#pragma once

#include "Common.h"
#include "TimeScaleController.h"



namespace ActionGame
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
		bool					m_IsGravity;

		//�d�͉����x
		float					m_Gravity;

		CHARA_TYPE				m_Type;

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
		Velocity();
			

		/**
		 * @brief		�X�V
		 */
		void Update();

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
		void SetVelocity(const Vector3& v) noexcept {
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

		void SetGravityFlg(bool isGravity) noexcept {
			m_IsGravity = isGravity;
		}

		void SetType(CHARA_TYPE type) noexcept
		{
			m_Type = type;
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

		bool IsGravity() const noexcept {
			return m_IsGravity;
		}

	};
	//�|�C���^�u������
	using VelocityPtr = std::shared_ptr<Velocity>;
}