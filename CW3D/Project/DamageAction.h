#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		ダメージアクション
	 */
	class DamageAction : public Action
	{
	public:

	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DamageAction()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {

			Velocity()->SetVelocity(Vector3(0.2f, 0.0f, 0.0f));
			Velocity()->SetDecelerate(0.05f,0.05f);
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
			return STATE_KEY_DAMAGE;
		}
	};
	//ポインタ置き換え
	using DamageActionPtr = std::shared_ptr<DamageAction>;
}
