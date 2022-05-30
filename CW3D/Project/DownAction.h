#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		ダメージアクション
	 */
	class DownAction : public Action
	{
	public:

	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DownAction()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			
			Velocity()->SetDecelerate(0.05f, 0.05f);
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
			return STATE_KEY_DOWN;
		}
	};
	//ポインタ置き換え
	using DownActionPtr = std::shared_ptr<DownAction>;
}
