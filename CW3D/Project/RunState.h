#pragma once

#include	"State.h"
#include	"RunAction.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunState : public State
	{
	private:
		/** 移動アクション */
		RunActionPtr			runAction_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunState()
			: State() {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			runAction_ = Actor()->GetAction<RunAction>(STATE_KEY_RUN);
			runAction_->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_RUN, 0.0f, 1.0f, 0.1f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			runAction_->Execution();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			//左右で移動
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
				Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				runAction_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}
			else
			{
				ChangeState(STATE_KEY_IDLE);
			}

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_RUNATTACK1);
			}
		}

		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
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
			return STATE_KEY_RUN;
		}
	};

}