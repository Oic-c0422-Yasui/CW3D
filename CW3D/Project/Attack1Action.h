#pragma once

#include	"Action.h"
#include	"MoveAction.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class Attack1Action : public Action
	{
	public:
		MoveActionPtr			m_MoveAction;
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
			m_MoveAction->Reset();
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
