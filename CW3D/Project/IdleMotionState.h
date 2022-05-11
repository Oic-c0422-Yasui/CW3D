#pragma once

#include	"State.h"
#include	"MoveAction.h"

namespace Sample {

	/**
	 * @brief		待機モーションステート
	 */
	class IdleMotionState : public State
	{
	private:
		/** 移動アクション */
		MoveActionPtr			m_MoveAction;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleMotionState()
			: State()
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			if (m_MoveAction->IsReverse())
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(180));
			}
			else
			{
				m_MoveAction->SetRotateY(0);

			}
			Actor()->GetAnimationState()->ChangeMotionByName("Idle", 1.0f, FALSE, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			//キーボードでの移動
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
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
			return STATE_KEY_IDLEMOTION;
		}
	};

}