#pragma once

#include "Common.h"

namespace Sample
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
		bool					useGravity;

		//重力加速度
		float					m_Gravity;


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
		 * @brief		更新
		 */
		void Update() {
			//重力の適用
			if (useGravity)
			{
				m_Velocity.y += m_Gravity;
				m_Velocity.y = ((m_Velocity.y > m_MaxVelocity.y) ?
					m_MaxVelocity.y : m_Velocity.y);
			}

			//回転の更新
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
			//速度の更新を実施
			if (fabsf(m_UpdateVelocity.x) > 0)
			{
				//最大速度を超えるようなら倍速で減速
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
				//最大速度を超えるようなら倍速で減速
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
		void SetVelocity(const CVector3& v) noexcept {
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
	};
	//ポインタ置き換え
	using VelocityPtr = std::shared_ptr<Velocity>;
}