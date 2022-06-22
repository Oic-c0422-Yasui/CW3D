#pragma once

#include	"State.h"
#include	"DeadAction.h"

namespace Sample {

	/**
	 * @brief		ダメージステート
	 */
	class DeadState : public State
	{
	private:
		//ダメージステート
		DeadActionPtr			m_DeadAction;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DeadState()
			: State()
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_DeadAction = Actor()->GetAction<DeadAction>(GetKey());
			m_DeadAction->Start();
			//Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_DOWN, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_DeadAction->Execution();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
		}

		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			m_DeadAction->End();
		}

		/**
	 * @brief		ステート内の接触イベント
	 * @param[in]	type		当たった相手のタイプ
	 * @param[in]	obj			当たった相手のオブジェクト
	 */
		void CollisionEvent(unsigned int type, std::any obj) override {
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override {
			return STATE_KEY_DEAD;
		}
	};
}
