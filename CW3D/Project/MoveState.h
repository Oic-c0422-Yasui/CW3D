#pragma once

#include	"State.h"
#include	"MoveAction.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class MoveState : public State
	{
	private:
		/** 移動アクション */
		MoveActionPtr			moveAction_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveState()
			: State() {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			moveAction_ = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Move",1.0f,TRUE,TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			//左右で移動
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED);
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED);
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			if(moveAction_->GetSpeedX() != 0.0f && moveAction_->GetSpeedZ() != 0.0f)
			{
				if (!moveAction_->IsMove())
				{
					ChangeState(STATE_KEY_IDLE);
				}
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
			return STATE_KEY_MOVE;
		}
	};

}