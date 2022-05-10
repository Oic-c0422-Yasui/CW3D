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
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Velocity()
			: m_Velocity()
			, m_MaxVelocity()
			, m_UpdateVelocity()
			, m_Decelerate()
			, useGravity(true)
			, m_Gravity()
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
	};
	//�|�C���^�u������
	using VelocityPtr = std::shared_ptr<Velocity>;
}