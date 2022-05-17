#pragma once

#include	"State.h"
#include	"MoveAction.h"

namespace Sample {

	/**
	 * @brief		待機ステート
	 */
	class IdleState : public State
	{
	private:
		/** 移動アクション */
		MoveActionPtr			m_MoveAction;
		float					m_Time;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleState()
			: State()
			, m_Time(0.0f)
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			m_Time = 0.0f;
			if (m_MoveAction->IsReverse())
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(90), 0.15f);
			}
			else
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(-90), 0.15f);

			}
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_IDLE, 0.0f, 1.0f, 0.15f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			if (m_Time < 5.0f)
			{
				m_Time += CUtilities::GetFrameSecond();
			}
			else
			{
				ChangeState(STATE_KEY_IDLEMOTION);
				
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
			{
				ChangeState(STATE_KEY_RUN);
				return;
			}
			//キーボードでの移動
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
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

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_ATTACK1);
			}

			//ボタンごとにスキルが変わる場合
			/*if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(setting.skill1SetName);
			}*/
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
			return STATE_KEY_IDLE;
		}
	};

}