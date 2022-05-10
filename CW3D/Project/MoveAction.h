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
			, m_ReverseFlg(false) {
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Exection() override {
			//移動がない場合減速
			if (!m_XMoveFlg)
			{
				DecelerateX(PLAYER_SPEED);
			}
			if (!m_ZMoveFlg)
			{
				DecelerateZ(PLAYER_SPEED);
			}
			//重力
			Gravity(GRAVITY);
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
			m_Move = Vector3(0, 0, 0);
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
		 * @param[in]	rev		反転フラグ
		 */
		void AccelerationX(float val, float maxspeed, bool reverse) {
			m_XMoveFlg  = true;
			m_Move.x += val;
			m_Move.x = ((m_Move.x > maxspeed) ? maxspeed : ((m_Move.x < -maxspeed) ? -maxspeed : m_Move.x));
			m_ReverseFlg = reverse;
		}

		/**
		 * @brief		加速
		 * @param[in]	val		加速量
		 */
		void Acceleration(float x, float maxspeed) {
			m_ZMoveFlg = true;
			m_Move.z += x;
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
		 *				横の移動速度が一定以下なら停止とみなす
		 */
		bool IsMove() const {
			return std::abs(m_Move.x) > 0.01f;
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

