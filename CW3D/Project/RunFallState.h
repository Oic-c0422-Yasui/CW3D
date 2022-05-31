#pragma once

#include	"State.h"
#include	"RunFallAction.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunFallState : public State
	{
	private:
		/** 移動アクション */
		RunFallActionPtr			m_FallAction;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunFallState()
			: State()
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_FallAction = Actor()->GetAction<RunFallAction>(GetKey());
			m_FallAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_JUMP, 0.83f, 1.0f, 0.2f, FALSE, MOTIONLOCK_OFF, FALSE);

		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_FallAction->Execution();
			// 落下状態への移行
			if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f &&
				Actor()->GetTransform()->GetPositionY() <= 0)
			{
				ChangeState(STATE_KEY_RUNLANDING);
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
				m_FallAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}



			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_RUNJUMPATTACK1);
			}

			//対応したスキルのボタンが押されていたらそのスキルのステートに移動
			for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
			{
				if (!Actor()->GetSkillController()->GetSkill(i)->GetCanUseFlg() || Actor()->GetSkillController()->GetSkill(i)->GetFlyState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
				{

					Actor()->GetSkillController()->GetSkill(i)->Start();
					ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
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
			return STATE_KEY_RUNFALL;
		}
	};

}