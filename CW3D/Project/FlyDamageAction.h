#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		ダメージアクション
	 */
	class FlyDamageAction : public Action
	{
	public:

	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		FlyDamageAction()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
			Velocity()->SetMaxGravity(GRAVITYMAX);
			Velocity()->SetGravity(GRAVITY);
			//Velocity()->SetVelocity(knockBack);
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
			return STATE_KEY_FLYDAMAGE;
		}
	};
	//ポインタ置き換え
	using FlyDamageActionPtr = std::shared_ptr<FlyDamageAction>;
}
