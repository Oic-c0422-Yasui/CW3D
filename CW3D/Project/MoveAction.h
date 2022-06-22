#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class MoveAction : public Action
	{
	public:
		/**
		* @brief		攻撃アクションの設定値
		*/
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;

			//減速値
			Vector3					decelerate;
			//加速値
			Vector3					velocity;
			Vector3					maxVelocity;

			float					maxGravity;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;

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
		MoveAction(Parameter param)
			: Action()
			, m_NowDirection(0)
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

			auto& vel = Velocity();
			//PLAYER_MAXSPEED * PLAYER_WALKSPEED
			vel->SetMaxVelocity(m_Parameter.maxVelocity.x, m_Parameter.maxVelocity.z);
			//GRAVITYMAX
			vel->SetMaxGravity(m_Parameter.maxGravity);
			//PLAYER_MAXSPEED * PLAYER_WALKSPEED
			vel->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				m_NowDirection = DIRECTION_RIGHT;
			}
			else
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				m_NowDirection = DIRECTION_LEFT;
			}
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override {

			auto& vel = Velocity();
			bool isReverse = Transform()->IsReverse();
			float rotateY = Transform()->GetRotateY();

			if (vel->GetVelocityX() < 0 && !isReverse)
			{
				Transform()->SetReverse(true);
				
				
			}
			else if (vel->GetVelocityX() > 0 && isReverse)
			{
				Transform()->SetReverse(false);
				
			}
			if (vel->GetVelocityX() < 0)
			{
				if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.15f);
					m_NowDirection = DIRECTION_LEFTUP;
				}
				else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.15f);
					m_NowDirection = DIRECTION_LEFTDOWN;
				}
				else if(vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
					m_NowDirection = DIRECTION_LEFT;
				}
			}
			else if (vel->GetVelocityX() > 0)
			{
				if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.15f);
					m_NowDirection = DIRECTION_RIGHTUP;
				}
				else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.15f);
					m_NowDirection = DIRECTION_RIGHTDOWN;
				}
				else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
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
			//PLAYER_SPEED * PLAYER_WALKSPEED
			Velocity()->Acceleration(x * m_Parameter.velocity.x,
				z * m_Parameter.velocity.z);
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

