#pragma once

#include "Common.h"
#include "TimeScaleController.h"



namespace ActionGame
{
	/**
	 * @brief		速度管理クラス
	 */
	class Velocity
	{
	protected:
		//速度
		CVector3				m_Velocity;

		//最大速度
		CVector3				m_MaxVelocity;

		//更新速度
		CVector3				m_UpdateVelocity;

		//減速値
		CVector3				m_Decelerate;

		//重力利用フラグ
		bool					m_IsGravity;

		//重力加速度
		float					m_Gravity;

		CHARA_TYPE				m_Type;

		//回転用変数
		bool					m_SetRotateFlg;
		float					m_CurrentTime;
		float					m_MoveTime;
		float					m_TargetY;
		float					m_StartY;
		float					m_CurrentY;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Velocity();
			

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
			m_UpdateVelocity.x += x;
			m_UpdateVelocity.z += z;
		}

		/**
		 * @brief		速度の設定
		 */
		void SetVelocity(const Vector3& v) noexcept {
			m_Velocity = v;
		}

		/**
		 * @brief		速度の設定
		 */
		void SetVelocity(float x, float z) noexcept {
			m_Velocity.x = x;
			m_Velocity.z = z;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocity(float x, float y, float z) noexcept {
			m_Velocity.x = x;
			m_Velocity.y = y;
			m_Velocity.z = z;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocityX(float x) noexcept {
			m_Velocity.x = x;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocityY(float y) noexcept {
			m_Velocity.y = y;
		}
		/**
		 * @brief		速度の設定
		 */
		void SetVelocityZ(float z) noexcept {
			m_Velocity.z = z;
		}
		/**
		 * @brief		最大速度の設定
		 */
		void SetMaxVelocity(float x, float z) noexcept {
			m_MaxVelocity.x = x;
			m_MaxVelocity.z = z;
		}
		/**
		 * @brief		減速設定
		 * @param[in]	x		減速量
		 * @param[in]	z		減速量
		 */
		void SetDecelerate(float x, float z) {
			m_Decelerate.x = x;
			m_Decelerate.z = z;
		}
		/**
		 * @brief		重力加速設定
		 * @param[in]	val		加速量
		 */
		void SetGravity(float val) {
			m_Gravity = val;
		}
		/**
		 * @brief		最大速度の設定
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
		 * @brief		速度の取得
		 */
		const CVector3& GetVelocity() const noexcept {
			return m_Velocity;
		}
		/**
		 * @brief		速度の取得
		 */
		float GetVelocityX() const noexcept {
			return m_Velocity.x;
		}
		/**
		 * @brief		速度の取得
		 */
		float GetVelocityY() const noexcept {
			return m_Velocity.y;
		}
		/**
		 * @brief		速度の取得
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
	//ポインタ置き換え
	using VelocityPtr = std::shared_ptr<Velocity>;
}