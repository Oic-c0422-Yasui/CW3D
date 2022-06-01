#pragma once


#include	"State.h"
#include	"RunJumpAttack3Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunJumpAttack3State : public State
	{
	private:
		/** 移動アクション */
		RunJumpAttack3ActionPtr			m_Attack3Action;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		std::vector<ShotPtr>		m_Shots;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack3State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_Attack3Action = Actor()->GetAction<RunJumpAttack3Action>(GetKey());
			m_FrameTime = 0;
			m_Attack3Action->Start();
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-0.7f, 0.7f, 0), Vector3(1.0f, 1.5f, 1.0f), attack,1.2f, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(0.7f, 0.7f, 0), Vector3(1.0f, 1.5f, 1.0f), attack,1.2f, 0));
			}

			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(Vector3(0.3f, 0.1f, 0));
			}
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK3, 0.0f, 1.5f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			for (auto& shot : m_Shots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime == 12 || m_FrameTime == 27)
				{
					shot->SetCollideFlg(true);
					if (m_FrameTime == 12)
					{
						m_Attack3Action->Execution();
					}

				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}

			m_FrameTime++;

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_FALL);
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
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
			for (auto& shot : m_Shots)
			{
				shot->SetShow(false);
				shot.reset();
			}
			m_Shots.clear();
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
			return STATE_KEY_RUNJUMPATTACK3;
		}
	};

}