#pragma once

#include "Common.h"
#include "TimeScaleController.h"



namespace ActionGame
{
	/**
	 * @brief		���x�Ǘ��N���X
	 */
	class CVelocity
	{
	protected:
		//���x
		CVector3				velocity_;

		//�ő呬�x
		CVector3				maxVelocity_;

		//�X�V���x
		CVector3				updateVelocity_;

		//�����l
		CVector3				decelerate_;

		//�d�͗��p�t���O
		bool					isUseGravity_;

		//�d�͉����x
		float					gravity_;

		CHARA_TYPE				type_;

		//��]�p�ϐ�
		bool					isSetRotate_;
		float					currentTime_;
		float					moveTime_;
		float					targetY_;
		float					startY_;
		float					currentY_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CVelocity();
			

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
			updateVelocity_.x += x;
			updateVelocity_.z += z;
		}

		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocity(const Vector3& v) noexcept {
			velocity_ = v;
		}

		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocity(float x, float z) noexcept {
			velocity_.x = x;
			velocity_.z = z;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocity(float x, float y, float z) noexcept {
			velocity_.x = x;
			velocity_.y = y;
			velocity_.z = z;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocityX(float x) noexcept {
			velocity_.x = x;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocityY(float y) noexcept {
			velocity_.y = y;
		}
		/**
		 * @brief		���x�̐ݒ�
		 */
		void SetVelocityZ(float z) noexcept {
			velocity_.z = z;
		}
		/**
		 * @brief		�ő呬�x�̐ݒ�
		 */
		void SetMaxVelocity(float x, float z) noexcept {
			maxVelocity_.x = x;
			maxVelocity_.z = z;
		}
		/**
		 * @brief		�����ݒ�
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void SetDecelerate(float x, float z) {
			decelerate_.x = x;
			decelerate_.z = z;
		}
		/**
		 * @brief		�d�͉����ݒ�
		 * @param[in]	val		������
		 */
		void SetGravity(float val) {
			gravity_ = val;
		}
		/**
		 * @brief		�ő呬�x�̐ݒ�
		 */
		void SetMaxGravity(float v) noexcept {
			maxVelocity_.y = v;
		}

		void SetRotateY(float startRotate,float endRotate, float time) {
			startY_ = startRotate;
			currentY_ = startY_;
			targetY_ = endRotate;
			moveTime_ = time;
			currentTime_ = 0;
			isSetRotate_ = true;
		}

		void SetGravityFlg(bool isGravity) noexcept {
			isUseGravity_ = isGravity;
		}

		void SetType(CHARA_TYPE type) noexcept
		{
			type_ = type;
		}

		/**
		 * @brief		���x�̎擾
		 */
		const CVector3& GetVelocity() const noexcept {
			return velocity_;
		}
		/**
		 * @brief		���x�̎擾
		 */
		float GetVelocityX() const noexcept {
			return velocity_.x;
		}
		/**
		 * @brief		���x�̎擾
		 */
		float GetVelocityY() const noexcept {
			return velocity_.y;
		}
		/**
		 * @brief		���x�̎擾
		 */
		float GetVelocityZ() const noexcept {
			return velocity_.z;
		}

		float GetRotateY() const noexcept {
			return currentY_;
		}

		bool IsGravity() const noexcept {
			return isUseGravity_;
		}

	};
	//�|�C���^�u������
	using VelocityPtr = std::shared_ptr<CVelocity>;
}