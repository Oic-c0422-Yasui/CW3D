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
		MoveActionPtr			m_MoveAction;
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
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Walk",1.0f,TRUE,TRUE);
			m_NowHorizontal = NO_DIRECTION;
			m_NowVertical = NO_DIRECTION;
			m_MoveAction->Start();
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
			InputDash();
			//左右で移動
			
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				
				
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);

			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);

			}

			

			if(!Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) && !Input()->IsPress(INPUT_KEY_HORIZONTAL) &&
				!Input()->IsNegativePress(INPUT_KEY_VERTICAL) && !Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				if (!m_MoveAction->IsMove())
				{
					ChangeState(STATE_KEY_IDLE);
				}
			}
		}

		void InputDash()
		{
			if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) || 
				Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
			{
					ChangeState(STATE_KEY_RUN);
					return;
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