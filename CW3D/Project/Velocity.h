#pragma once

#include "Common.h"
#include "TimeScaleController.h"



namespace ActionGame
{
	/**
	 * @brief		速度管理クラス
	 */
	class CVelocity
	{
	protected:
		//速度
		CVector3				velocity_;

		//最大速度
		CVector3				maxVelocity_;

		//更新速度
		CVector3				updateVelocity_;

		//減速値
		CVector3				decelerate_;

		//重力利用フラグ
		bool					isUseGravity_;

		//重力加速度
		float					gravity_;

		CHARA_TYPE				type_;

		//回転用変数
		bool					isSetRotate_;
		float					currentTime_;
		float					moveTime_;
		float					targetY_;
		float					startY_;
		float					currentY_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CVelocity();
			

		/**
		 * @brief		更新
		 */
		void Update();

		/**
		 * @brief		加速
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Acceleration(float x, float z) {
			updateVelocity_.x += x;
			updateVelocity_.z += z;
		}

		/**
		 * @brief		速度の設定
		 */
		void SetVelocity(const Vector3& v) noexcept {
			velocity_ = v;
		}

		/**
		 * @brief		速度の設定
		 */
		void SetVelocity(float x, float z) noexcept {
			velocity_.x = x;
			velocity_.z = z;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocity(float x, float y, float z) noexcept {
			velocity_.x = x;
			velocity_.y = y;
			velocity_.z = z;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocityX(float x) noexcept {
			velocity_.x = x;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocityY(float y) noexcept {
			velocity_.y = y;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocityZ(float z) noexcept {
			velocity_.z = z;
		}
		/**
		 * @brief		最大速度の設定
		 */
		void SetMaxVelocity(float x, float z) noexcept {
			maxVelocity_.x = x;
			maxVelocity_.z = z;
		}
		/**
		 * @brief		減速設定
		 * @param[in]	x		減速量
		 * @param[in]	z		減速量
		 */
		void SetDecelerate(float x, float z) {
			decelerate_.x = x;
			decelerate_.z = z;
		}
		/**
		 * @brief		重力加速設定
		 * @param[in]	val		加速量
		 */
		void SetGravity(float val) {
			gravity_ = val;
		}
		/**
		 * @brief		最大速度の設定
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
		 * @brief		速度の取得
		 */
		const CVector3& GetVelocity() const noexcept {
			return velocity_;
		}
		/**
		 * @brief		速度の取得
		 */
		float GetVelocityX() const noexcept {
			return velocity_.x;
		}
		/**
		 * @brief		速度の取得
		 */
		float GetVelocityY() const noexcept {
			return velocity_.y;
		}
		/**
		 * @brief		速度の取得
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
	//ポインタ置き換え
	using VelocityPtr = std::shared_ptr<CVelocity>;
}