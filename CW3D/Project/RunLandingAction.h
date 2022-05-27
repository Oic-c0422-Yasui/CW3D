#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class RunLandingAction : public Action
	{
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunLandingAction()
			: Action()

		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& vel = Velocity();

			//vel->SetDecelerate(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);

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


		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
		}



		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_RUNLANDING;
		}
	};
	//ポインタ置き換え
	using RunLandingActionPtr = std::shared_ptr<RunLandingAction>;
}

