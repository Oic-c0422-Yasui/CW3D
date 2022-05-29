#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class RunAction : public Action
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
		RunAction()
			: Action()
			, m_NowDirection(-1)
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& vel = Velocity();
			vel->SetMaxVelocity(PLAYER_MAXSPEED, PLAYER_MAXSPEED);

			vel->SetMaxGravity(GRAVITYMAX);
			vel->SetDecelerate(PLAYER_SPEED, PLAYER_SPEED);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				m_NowDirection = DIRECTION_RIGHT;
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				m_NowDirection = DIRECTION_LEFT;
			}
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override {
			//移動がない場合減速

			auto& velocity = Velocity();
			bool isReverse = Transform()->IsReverse();
			float rotateY = Transform()->GetRotateY();

			if (velocity->GetVelocityX() < 0 && !isReverse)
			{
				Transform()->SetReverse(true);
			}
			else if (velocity->GetVelocityX() > 0 && isReverse)
			{
				
				Transform()->SetReverse(false);
			}
			if (velocity->GetVelocityX() < 0)
			{
				if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.15f);
					m_NowDirection = DIRECTION_LEFTUP;
				}
				else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.15f);
					m_NowDirection = DIRECTION_LEFTDOWN;
				}
				else if (velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
					m_NowDirection = DIRECTION_LEFT;
				}
			}
			else if (velocity->GetVelocityX() > 0)
			{
				if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.15f);
					m_NowDirection = DIRECTION_RIGHTUP;
				}
				else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.15f);
					m_NowDirection = DIRECTION_RIGHTDOWN;
				}
				else if (velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.15f);
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
			return STATE_KEY_RUN;
		}
	};
	//ポインタ置き換え
	using RunActionPtr = std::shared_ptr<RunAction>;

}

