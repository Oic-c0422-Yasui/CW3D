#pragma once

#include	"State.h"
#include	"RunJumpAction.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunJumpState : public State
	{
	private:
		/** 移動アクション */
		RunJumpActionPtr			m_JumpAction;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpState()
			: State()
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_JumpAction = Actor()->GetAction<RunJumpAction>(GetKey());
			m_JumpAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_JUMP, 0.3f, 2.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);

		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_JumpAction->Execution();
			// 落下状態への移行
			if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
			{
				ChangeState(STATE_KEY_RUNFALL);
			}
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
				m_JumpAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}


			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_RUNJUMPATTACK1);
			}

			//対応したスキルのボタンが押されていたらそのスキルのステートに移動
			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (!SkillManagerInstance.GetSkill(i)->GetCanUseFlg() || SkillManagerInstance.GetSkill(i)->GetFlyState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(SkillManagerInstance.GetSkill(i)->GetButton()))
				{

					SkillManagerInstance.GetSkill(i)->Start();
					ChangeState(SkillManagerInstance.GetSkill(i)->GetFlyState());
					break;
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
			return STATE_KEY_RUNJUMP;
		}
	};

}