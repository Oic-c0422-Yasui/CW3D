#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class RunJumpAction : public Action
	{
	private:
		int m_NowDirection;
		enum tag_DIRECTION
		{
			DIRECTION_RIGHT,
			DIRECTION_RIGHTUP,
			DIRECTION_RIGHTDOWN,
			DIRECTION_LEFT,
			DIRECTION_LEFTUP,
			DIRECTION_LEFTDOWN,
		};
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAction()
			: Action()

		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& vel = Velocity();

			vel->SetMaxVelocity(PLAYER_MAXSPEED, PLAYER_MAXSPEED);

			vel->SetMaxGravity(GRAVITYMAX);
			//vel->SetDecelerate(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
			vel->SetVelocityY(PLAYER_JUMPPOWER);
			vel->SetGravity(GRAVITY);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				m_NowDirection = DIRECTION_LEFT;
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				m_NowDirection = DIRECTION_RIGHT;
			}
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override {

			auto& velocity = Velocity();
			bool isReverse = Transform()->IsReverse();
			float rotateY = Transform()->GetRotateY();

			if (Transform()->IsReverse())
			{
				if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.1f);
					m_NowDirection = DIRECTION_LEFTUP;
				}
				else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.1f);
					m_NowDirection = DIRECTION_LEFTDOWN;
				}
				else if (velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.1f);
					m_NowDirection = DIRECTION_LEFT;
				}
			}
			else
			{
				if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.1f);
					m_NowDirection = DIRECTION_RIGHTUP;
				}
				else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.1f);
					m_NowDirection = DIRECTION_RIGHTDOWN;
				}
				else if (velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.1f);
					m_NowDirection = DIRECTION_RIGHT;
				}
			}
		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
		}

		/**
		 * @brief		加速
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Acceleration(float x, float z) {
			Velocity()->Acceleration(x * PLAYER_SPEED,
				z * PLAYER_SPEED);
		}


		/**
		 * @brief		速度リセット
		 */
		void Reset() {

		}



		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_RUNJUMP;
		}
	};
	//ポインタ置き換え
	using RunJumpActionPtr = std::shared_ptr<RunJumpAction>;
}

