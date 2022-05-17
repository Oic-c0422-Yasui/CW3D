#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class Attack1Action : public Action
	{
	public:
	private:
		//パラメーター

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Attack1Action()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			
			Velocity()->SetDecelerate(PLAYER_SPEED * 0.3f, PLAYER_SPEED * 0.3f);
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Exection() override {
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
			return STATE_KEY_ATTACK1;
		}
	};
	//ポインタ置き換え
	using Attack1ActionPtr = std::shared_ptr<Attack1Action>;
}
