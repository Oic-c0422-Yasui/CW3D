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
		BYTE					m_NowHorizontal;
		BYTE					m_NowVertical;
		enum Tag_Direction
		{
			NO_DIRECTION = 0,
			PLUS_DIRECTION,
			MINUS_DIRECTION,
		};
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveState()
			: State()
			, m_NowHorizontal(NO_DIRECTION)
			, m_NowVertical(NO_DIRECTION)
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			moveAction_ = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Walk",1.0f,TRUE,TRUE);
			m_NowHorizontal = NO_DIRECTION;
			m_NowVertical = NO_DIRECTION;
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
				moveAction_->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowHorizontal == MINUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowHorizontal = MINUS_DIRECTION;
				}
				
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowHorizontal == PLUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowHorizontal = PLUS_DIRECTION;
				}
				
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowVertical == PLUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowVertical = PLUS_DIRECTION;
				}
			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowVertical == MINUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowVertical = MINUS_DIRECTION;
				}
			}
			if (moveAction_->IsReverse())
			{
				moveAction_->SetRotateY(MOF_ToRadian(90));
			}
			else
			{
				moveAction_->SetRotateY(MOF_ToRadian(-90));
			}
			if(!Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) && !Input()->IsPress(INPUT_KEY_HORIZONTAL) &&
				!Input()->IsNegativePress(INPUT_KEY_VERTICAL) && !Input()->IsPress(INPUT_KEY_VERTICAL))
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