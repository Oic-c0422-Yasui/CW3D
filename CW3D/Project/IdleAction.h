#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		移動アクション
	 */
	class IdleAction : public Action
	{
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleAction()
			: Action()

		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& vel = Velocity();

			vel->SetDecelerate(PLAYER_SPEED * 0.3f, PLAYER_SPEED * 0.3f);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.15f);
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
			return STATE_KEY_IDLE;
		}
	};
	//ポインタ置き換え
	using IdleActionPtr = std::shared_ptr<IdleAction>;

}

