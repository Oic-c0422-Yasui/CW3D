#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class MoveAction : public Action
	{
	private:
		/** 横移動フラグ */
		bool			m_XMoveFlg;
		/** 縦移動フラグ */
		bool			m_ZMoveFlg;

		float m_SetRotateFlg;
		float m_TargetY;
		float m_MoveTime;
		float m_StartY;
		float m_CurrentTime;
		/** 移動量 */
		CVector3 m_Move;

		/** 反転フラグ */
		bool			m_ReverseFlg;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveAction()
			: Action()
			, m_XMoveFlg(false)
			, m_ZMoveFlg(false)
			, m_Move(0,0,0)
			, m_ReverseFlg(false)
			, m_TargetY(0.0f)
			, m_MoveTime(0.0f)
			, m_StartY(0.0f)
			, m_CurrentTime(0.0f)
			, m_SetRotateFlg(false)
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			if (m_ReverseFlg)
			{
				SetRotateY(MOF_ToRadian(90), 0.2f);
			}
			else
			{
				SetRotateY(MOF_ToRadian(-90), 0.2f);
			}
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Exection() override {
			//移動がない場合減速
			if (!m_XMoveFlg)
			{
				DecelerateX(PLAYER_SPEED * 0.5);
			}
			if (!m_ZMoveFlg)
			{
				DecelerateZ(PLAYER_SPEED * 0.5);
			}
			if (m_Move.x > 0 && m_ReverseFlg)
			{
				m_ReverseFlg = false;
				SetRotateY(MOF_ToRadian(-90), 0.2f);

			}
			else if (m_Move.x < 0 && !m_ReverseFlg)
			{
				m_ReverseFlg = true;
				SetRotateY(MOF_ToRadian(90), 0.2f);
			}

			if (m_CurrentTime > m_MoveTime && m_SetRotateFlg)
			{
				Transform()->SetRotateY(m_TargetY);
				m_SetRotateFlg = false;
			}
			else if(m_SetRotateFlg)
			{
				float t = m_CurrentTime / m_MoveTime;
				Transform()->SetRotateY(m_StartY + (m_TargetY - m_StartY) * t);
				m_CurrentTime += CUtilities::GetFrameSecond();
			}

			//重力
			//Gravity(GRAVITY);
			//実際に座標を移動させる
			Transform()->MovePosition(m_Move);
			//移動フラグOFF
			m_XMoveFlg = false;
			m_ZMoveFlg = false;
		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
		}

		/**
		 * @brief		速度リセット
		 */
		void Reset() {
			m_XMoveFlg = false;
			m_ZMoveFlg = false;
			//m_Move = Vector3(0, 0, 0);
			m_ReverseFlg = false;
		}

		/**
		 * @brief		重力加速
		 * @param[in]	val		加速量
		 */
		void Gravity(float val) {
			m_Move.y += val;
			if (m_Move.y >= GRAVITYMAX)
			{
				m_Move.y = GRAVITYMAX;
			}
		}

		/**
		 * @brief		加速
		 * @param[in]	val		加速量
		 */
		void AccelerationX(float val, float maxspeed) {
			m_XMoveFlg  = true;
			m_Move.x += val;
			m_Move.x = ((m_Move.x > maxspeed) ? maxspeed : ((m_Move.x < -maxspeed) ? -maxspeed : m_Move.x));
		}

		/**
		 * @brief		加速
		 * @param[in]	val		加速量
		 */
		void AccelerationZ(float speed, float maxspeed) {
			m_ZMoveFlg = true;
			m_Move.z += speed;
			m_Move.z = ((m_Move.z > maxspeed) ? maxspeed : ((m_Move.z < -maxspeed) ? -maxspeed : m_Move.z));
		}

		/**
		 * @brief		減速
		 * @param[in]	dec		減速量
		 */
		void DecelerateX(float dec) {
			if (m_Move.x > 0)
			{
				m_Move.x -= dec;
				if (m_Move.x <= 0)
				{
					m_Move.x = 0;
				}
			}
			else if (m_Move.x < 0)
			{
				m_Move.x += dec;
				if (m_Move.x >= 0)
				{
					m_Move.x = 0;
				}
			}
		}

		/**
		 * @brief		減速
		 * @param[in]	dec		減速量
		 */
		void DecelerateZ(float dec) {
			if (m_Move.z > 0)
			{
				m_Move.z -= dec;
				if (m_Move.z <= 0)
				{
					m_Move.z = 0;
				}
			}
			else if (m_Move.z < 0)
			{
				m_Move.z += dec;
				if (m_Move.z >= 0)
				{
					m_Move.z = 0;
				}
			}
		}

		/**
		 * @brief		速度設定
		 * @param[in]	val		速度
		 */
		void SetSpeed(float val) {
			m_Move.x = val;
			m_Move.z = val;
		}

		/**
		 * @brief		速度設定
		 * @param[in]	val		速度
		 */
		void SetSpeedX(float val) {
			m_Move.x = val;
		}

		/**
		 * @brief		速度設定
		 * @param[in]	val		速度
		 */
		void SetSpeedY(float val) {
			m_Move.y = val;
		}

		/**
		 * @brief		速度設定
		 * @param[in]	val		速度
		 */
		void SetSpeedZ(float val) {
			m_Move.y = val;
		}

		void SetReverseFlg(bool isReverse)
		{
			m_ReverseFlg = isReverse;
		}

		void SetRotateY(float val,float time) {
			m_TargetY = val;
			m_MoveTime = time;
			m_StartY = Transform()->GetRotateY();
			m_CurrentTime = 0;
			m_SetRotateFlg = true;
		}

		/**
		 * @brief		速度取得
		 */
		float GetSpeedX() {
			return m_Move.x;
		}

		/**
		 * @brief		速度取得
		 */
		float GetSpeedY() {
			return m_Move.y;
		}

		/**
		 * @brief		速度取得
		 */
		 float GetSpeedZ() {
			return m_Move.z;
		}

		/**
		 * @brief		反転フラグ
		 */
		bool IsReverse() const {
			return m_ReverseFlg;
		}

		/**
		 * @brief		移動判断
		 *				移動速度が一定以下なら停止とみなす
		 */
		bool IsMove() const {
			if (std::abs(m_Move.x) > 0.01f || std::abs(m_Move.z) > 0.01f)
			{
				return true;
			}
			return false;
		}



		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_MOVE;
		}
	};
	//ポインタ置き換え
	using MoveActionPtr = std::shared_ptr<MoveAction>;

}

