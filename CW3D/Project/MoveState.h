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
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveState()
			: State()
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);
			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);
			}
			m_MoveAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_MOVE, 0.0f, 1.0f, 0.1f, TRUE, MOTIONLOCK_OFF, TRUE);
			
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_MoveAction->Execution();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			InputDash();
			//左右で移動
			
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
				Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}
			else
			{
				ChangeState(STATE_KEY_IDLE);
			}

			if (Input()->IsPush(INPUT_KEY_JUMP))
			{
				ChangeState(STATE_KEY_JUMP);
			}


			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_ATTACK1);
			}

			//対応したスキルのボタンが押されていたらそのスキルのステートに移動
			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (!SkillManagerInstance.GetSkill(i)->GetCanUseFlg())
				{
					continue;
				}
				if (Input()->IsPush(SkillManagerInstance.GetSkill(i)->GetButton()))
				{
					ChangeState(SkillManagerInstance.GetSkill(i)->GetName());
					break;
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