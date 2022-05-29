#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class JumpAttack1Action : public Action
	{
	public:
	private:
		//パラメーター

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JumpAttack1Action()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {

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
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_JUMPATTACK1;
		}
	};
	//ポインタ置き換え
	using JumpAttack1ActionPtr = std::shared_ptr<JumpAttack1Action>;
}
