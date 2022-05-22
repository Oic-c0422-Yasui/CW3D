#pragma once

#include "Common.h"

namespace Sample
{
	/**
	 * @brief		���x�Ǘ��N���X
	 */
	class Velocity
	{
	protected:
		//���x
		CVector3				m_Velocity;

		//�ő呬�x
		CVector3				m_MaxVelocity;

		//�X�V���x
		CVector3				m_UpdateVelocity;

		//�����l
		CVector3				m_Decelerate;

		//�d�͗��p�t���O
		bool					useGravity;

		//�d�͉����x
		float					m_Gravity;


		//��]�p�ϐ�
		bool					m_SetRotateFlg;
		float					m_CurrentTime;
		float					m_MoveTime;
		float					m_TargetY;
		float					m_StartY;
		float					m_CurrentY;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Velocity()
			: m_Velocity(0.0f, 0.0f, 0.0f)
			, m_MaxVelocity(0.0f, 0.0f, 0.0f)
			, m_UpdateVelocity(0.0f, 0.0f, 0.0f)
			, m_Decelerate(0.0f, 0.0f, 0.0f)
			, useGravity(true)
			, m_Gravity(0.0f)
			, m_SetRotateFlg(false)
			, m_CurrentTime(0.0f)
			, m_MoveTime(0.0f)
			, m_TargetY(0.0f)
			, m_StartY(0.0f)
			, m_CurrentY(0.0f)
		{
		}

		/**
		 * @brief		�X�V
		 */
		void Update() {
			//�d�͂̓K�p
			if (useGravity)
			{
				m_Velocity.y += m_Gravity;
				m_Velocity.y = ((m_Velocity.y > m_MaxVelocity.y) ?
					m_MaxVelocity.y : m_Velocity.y);
			}

			//��]�̍X�V
			if (m_SetRotateFlg)
			{
				if (m_CurrentTime <= m_MoveTime)
				{
					m_CurrentY = MyUtilities::RotateTimer(m_StartY, m_CurrentTime, m_TargetY, m_MoveTime);

					m_CurrentTime += CUtilities::GetFrameSecond();
				}
				else
				{
					m_CurrentY = m_TargetY;
					m_SetRotateFlg = false;
				}
			}
			//���x�̍X�V�����{
			if (fabsf(m_UpdateVelocity.x) > 0)
			{
				//�ő呬�x�𒴂���悤�Ȃ�{���Ō���
				if (m_Velocity.x > m_MaxVelocity.x + m_Decelerate.x * 2)
				{
					m_Velocity.x -= m_Decelerate.x * 2;
					if (m_UpdateVelocity.x < 0)
					{
						m_Velocity.x += m_UpdateVelocity.x;
					}
				}
				else if (m_Velocity.x < -m_MaxVelocity.x - m_Decelerate.x * 2)
				{
					m_Velocity.x += m_Decelerate.x * 2;
					if (m_UpdateVelocity.x > 0)
					{
						m_Velocity.x += m_UpdateVelocity.x;
					}
				}
				else
				{
					m_Velocity.x += m_UpdateVelocity.x;
					m_Velocity.x = ((m_Velocity.x > m_MaxVelocity.x) ?
						m_MaxVelocity.x : ((m_Velocity.x < -m_MaxVelocity.x) ?
							-m_MaxVelocity.x : m_Velocity.x));
				}
				m_UpdateVelocity.x = 0;
			}
			else
			{
				m_Velocity.x = ((fabsf(m_Velocity.x) < fabsf(m_Decelerate.x)) ?
					0 : m_Velocity.x - copysignf(m_Decelerate.x, m_Velocity.x));
			}
			if (fabsf(m_UpdateVelocity.z) > 0)
			{
				//�ő呬�x�𒴂���悤�Ȃ�{���Ō���
				if (m_Velocity.z > m_MaxVelocity.z + m_Decelerate.z * 2)
				{
					m_Velocity.z -= m_Decelerate.z * 2;
					if (m_UpdateVelocity.z < 0)
					{
						m_Velocity.z += m_UpdateVelocity.z;
					}
				}
				else if (m_Velocity.z < -m_MaxVelocity.z - m_Decelerate.z * 2)
				{
					m_Velocity.z += m_Decelerate.z * 2;
					if (m_UpdateVelocity.z > 0)
					{
						m_Velocity.z += m_UpdateVelocity.z;
					}
				}
				else
				{
					m_Velocity.z += m_UpdateVelocity.z;
					m_Velocity.z = ((m_Velocity.z > m_MaxVelocity.z) ?
						m_MaxVelocity.z : ((m_Velocity.z < -m_MaxVelocity.z) ?
							-m_MaxVelocity.z : m_Velocity.z));
				}
				m_UpdateVelocity.z = 0;
			}
			else
			{
				m_Velocity.z = ((fabsf(m_Velocity.z) < fabsf(m_Decelerate.z)) ?
					0 : m_Velocity.z - copysignf(m_Decelerate.z, m_Velocity.z));
			}
		}

		/**
		 * @brief		����
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void Acceleration(float x, float z) {
			m_UpdateVelocity.x += x;
			m_UpdateVelocity.z += z;
		}

		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocity(const CVector3& v) noexcept {
			m_Velocity = v;
		}

		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocity(float x, float z) noexcept {
			m_Velocity.x = x;
			m_Velocity.z = z;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocity(float x, float y, float z) noexcept {
			m_Velocity.x = x;
			m_Velocity.y = y;
			m_Velocity.z = z;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocityX(float x) noexcept {
			m_Velocity.x = x;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocityY(float y) noexcept {
			m_Velocity.y = y;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocityZ(float z) noexcept {
			m_Velocity.z = z;
		}
		/**
		 * @brief		�ő呬�x�̐ݒ�
		 */
		void SetMaxVelocity(float x, float z) noexcept {
			m_MaxVelocity.x = x;
			m_MaxVelocity.z = z;
		}
		/**
		 * @brief		�����ݒ�
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void SetDecelerate(float x, float z) {
			m_Decelerate.x = x;
			m_Decelerate.z = z;
		}
		/**
		 * @brief		�d�͉����ݒ�
		 * @param[in]	val		������
		 */
		void SetGravity(float val) {
			m_Gravity = val;
		}
		/**
		 * @brief		�ő呬�x�̐ݒ�
		 */
		void SetMaxGravity(float v) noexcept {
			m_MaxVelocity.y = v;
		}

		void SetRotateY(float startRotate,float endRotate, float time) {
			m_StartY = startRotate;
			m_CurrentY = m_StartY;
			m_TargetY = endRotate;
			m_MoveTime = time;
			m_CurrentTime = 0;
			m_SetRotateFlg = true;
		}

		/**
		 * @brief		���x�̎擾
		 */
		const CVector3& GetVelocity() const noexcept {
			return m_Velocity;
		}
		/**
		 * @brief		���x�̎擾
		 */
		float GetVelocityX() const noexcept {
			return m_Velocity.x;
		}
		/**
		 * @brief		���x�̎擾
		 */
		float GetVelocityY() const noexcept {
			return m_Velocity.y;
		}
		/**
		 * @brief		���x�̎擾
		 */
		float GetVelocityZ() const noexcept {
			return m_Velocity.z;
		}

		float GetRotateY() const noexcept {
			return m_CurrentY;
		}
	};
	//�|�C���^�u������
	using VelocityPtr = std::shared_ptr<Velocity>;
}