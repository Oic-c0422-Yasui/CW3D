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

		//��]�p�\����
		struct RotateParam
		{
			bool					isStart;
			float					currentTime;
			float					endTime;
			float					targetY;
			float					startY;
			float					currentY;
			RotateParam()
			{
				isStart = false;
				currentTime = 0.0f;
				endTime = 0.0f;
				targetY = 0.0f;
				startY = 0.0f;
				currentY = 0.0f;
			}
		};
		RotateParam rotate_;

		//�d�̓X�P�[���p�\����
		struct GravityScaleParam
		{
			bool					isStart;
			float					currentTime;
			float					endTime;
			float					targetScale;
			float					startScale;
			float					currentScale;
			GravityScaleParam()
			{
				isStart = false;
				currentTime = 0.0f;
				endTime = 0.0f;
				targetScale = 0.0f;
				startScale = 0.0f;
				currentScale = 1.0f;
			}
		};
		GravityScaleParam gravityScale_;


	protected:
		void UpdateRotate();
		void UpdateGravity();
		void UpdateGravityScale();
		void UpdateVelocity();

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
		void SetGravity(float val)  noexcept {
			gravity_ = val;
		}
		/*
		* @brief	�d�̓X�P�[���ݒ�
		* @param[in]	startScale	�J�n�d�̓X�P�[��
		* @param[in]	endScale	�I���d�̓X�P�[��
		* @param[in]	time		�J�n�X�P�[���p������
		*/
		void SetGravityScale(float startScale,float endScale,float time) {
			gravityScale_.startScale = startScale;
			gravityScale_.currentScale = gravityScale_.startScale;
			gravityScale_.targetScale = endScale;
			gravityScale_.endTime = time;
			gravityScale_.currentTime = 0;
			gravityScale_.isStart = true;
		}
		/*
		* @brief	�d�̓X�P�[���ݒ�
		* @param[in]	startScale	�J�n�d�̓X�P�[��
		* @param[in]	endScale	�I���d�̓X�P�[��
		* @param[in]	time		�J�n�X�P�[���p������
		*/
		void SetGravityScale(float startScale, float time) {
			SetGravityScale(startScale, gravityScale_.currentScale, time);
		}

		/**
		 * @brief		�ő呬�x�̐ݒ�
		 */
		void SetMaxGravity(float v) noexcept {
			maxVelocity_.y = v;
		}

		void SetRotateY(float startRotate,float endRotate, float time) {
			rotate_.startY = startRotate;
			rotate_.currentY = rotate_.startY;
			rotate_.targetY = endRotate;
			rotate_.endTime = time;
			rotate_.currentTime = 0;
			rotate_.isStart = true;
		}

		void SetIsGravity(bool isGravity) noexcept {
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
			return rotate_.currentY;
		}

		bool IsGravity() const noexcept {
			return isUseGravity_;
		}

		bool GetGravityScale() const noexcept {
			return gravityScale_.currentScale;
		}

	};
	//�|�C���^�u������
	using VelocityPtr = std::shared_ptr<CVelocity>;
}