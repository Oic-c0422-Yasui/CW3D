#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class JumpSkill2_1Action : public Action
	{
	public:
	private:
		//パラメーター

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JumpSkill2_1Action()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			Velocity()->SetGravityFlg(false);
			Velocity()->SetDecelerate(PLAYER_SPEED * 0.3f, PLAYER_SPEED * 0.3f);
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
			Velocity()->SetGravityFlg(true);
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_JUMPSKILL2_1;
		}
	};
	//ポインタ置き換え
	using JumpSkill2_1ActionPtr = std::shared_ptr<JumpSkill2_1Action>;
}
