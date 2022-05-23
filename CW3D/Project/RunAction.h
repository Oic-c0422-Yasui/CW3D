#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class RunAction : public Action
	{
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunAction()
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
			vel->SetDecelerate(PLAYER_SPEED, PLAYER_SPEED);

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
		void Execution() override {
			//移動がない場合減速

			auto& velocity = Velocity();
			bool isReverse = Transform()->IsReverse();

			if (velocity->GetVelocityX() < 0 && !isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(true);
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
			}
			else if (velocity->GetVelocityX() > 0 && isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(false);
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
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

