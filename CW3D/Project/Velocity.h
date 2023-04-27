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

		//回転用構造体
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

		//重力スケール用構造体
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
		void SetGravity(float val)  noexcept {
			gravity_ = val;
		}
		/*
		* @brief	重力スケール設定
		* @param[in]	startScale	開始重力スケール
		* @param[in]	endScale	終了重力スケール
		* @param[in]	time		開始スケール継続時間
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
		* @brief	重力スケール設定
		* @param[in]	startScale	開始重力スケール
		* @param[in]	endScale	終了重力スケール
		* @param[in]	time		開始スケール継続時間
		*/
		void SetGravityScale(float startScale, float time) {
			SetGravityScale(startScale, gravityScale_.currentScale, time);
		}

		/**
		 * @brief		最大速度の設定
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
			return rotate_.currentY;
		}

		bool IsGravity() const noexcept {
			return isUseGravity_;
		}

		bool GetGravityScale() const noexcept {
			return gravityScale_.currentScale;
		}

	};
	//ポインタ置き換え
	using VelocityPtr = std::shared_ptr<CVelocity>;
}