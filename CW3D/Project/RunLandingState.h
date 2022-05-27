#pragma once

#include	"State.h"
#include	"RunLandingAction.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunLandingState : public State
	{
	private:
		/** 移動アクション */
		RunLandingActionPtr			m_LandingAction;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunLandingState()
			: State()
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_LandingAction = Actor()->GetAction<RunLandingAction>(GetKey());
			m_LandingAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_LANDING, 0.0f, 1.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);

		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_LandingAction->Execution();
			// 落下状態への移行
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
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
				ChangeState(STATE_KEY_RUN);
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
			return STATE_KEY_RUNLANDING;
		}
	};

}