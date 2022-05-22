#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class MoveAction : public Action
	{
	private:

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
			auto& vel = Velocity();
			vel->SetMaxVelocity(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				
			vel->SetMaxGravity(GRAVITYMAX);
			vel->SetDecelerate(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
			}
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Exection() override {

			auto& velocity = Velocity();
			bool isReverse = Transform()->IsReverse();
			
			if (velocity->GetVelocityX() < 0 && !isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(true);
				Velocity()->SetRotateY(rotateY,MOF_ToRadian(90), 0.1f);
			}
			else if (velocity->GetVelocityX() > 0 && isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(false);
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.1f);
			}
			/*if (!m_XMoveFlg)
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
			}*/

			/*if (m_CurrentTime > m_MoveTime && m_SetRotateFlg)
			{
				Transform()->SetRotateY(m_TargetY);
				m_SetRotateFlg = false;
			}
			else if (m_SetRotateFlg)
			{

				float rotateY = MyUtilities::RotateTimer(m_StartY, m_CurrentTime, m_TargetY, m_MoveTime);

				Transform()->SetRotateY(rotateY);
				m_CurrentTime += CUtilities::GetFrameSecond();
			}*/


			//重力
			//Gravity(GRAVITY);
			//実際に座標を移動させる
			/*Transform()->MovePosition(m_Move);*/
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
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Acceleration(float x, float z) {
			Velocity()->Acceleration(x * (PLAYER_SPEED * PLAYER_WALKSPEED),
				z *(PLAYER_SPEED * PLAYER_WALKSPEED));
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

