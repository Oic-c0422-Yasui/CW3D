#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class RunJumpAttack2Action : public Action
	{
	public:
	private:
		//パラメーター

	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack2Action()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& vel = Velocity();
			vel->SetVelocityY(PLAYER_JUMPPOWER * 0.7f);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				Velocity()->SetVelocityX(-0.15f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				Velocity()->SetVelocityX(0.15f);
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
			return STATE_KEY_RUNJUMPATTACK2;
		}
	};
	//ポインタ置き換え
	using RunJumpAttack2ActionPtr = std::shared_ptr<RunJumpAttack2Action>;
}
