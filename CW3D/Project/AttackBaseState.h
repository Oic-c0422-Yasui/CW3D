#pragma once


#include	"State.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class AttackBaseState : public State
	{
	protected:

		int								m_FrameTime;

		std::vector<ShotPtr>			m_Shots;
		EffectPtr						m_Effect;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		AttackBaseState()
			: State()
		{
		}
		virtual const ShotAABB& GetCreateShotStatusAABB() = 0;
		virtual const ShotSphere& GetCreateShotStatusSphere() = 0;

		virtual void CreateShotAABB()
		{
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			ShotAABB status = GetCreateShotStatusAABB();
			status.damage += attack;
			if (Actor()->IsReverse())
			{
				status.offset.x *= -1;
			}

			m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
		}
		virtual void CreateShotSphere()
		{
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			ShotSphere status = GetCreateShotStatusSphere();
			status.damage += attack;
			if (Actor()->IsReverse())
			{
				status.offset.x *= -1;
			}

			m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
		}
		/**
		 * @brief		ステート内の開始処理
		 */
		virtual void Start() override {

		}

		/**
		 * @brief		ステート内の実行処理
		 */
		virtual void Execution() override {


		}

		/**
		 * @brief		ステート内の入力処理
		 */
		virtual void InputExecution() override {

			//対応したスキルのボタンが押されていたらそのスキルのステートに移動
			for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
			{
				SKillPtr skill = Actor()->GetSkillController()->GetSkill(i);
				if (!skill->GetCanUseFlg() || skill->GetState() == NULL || skill->GetFlyState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(skill->GetButton()))
				{

					skill->Start();
					if (Actor()->GetPositionY() > 0)
					{
						ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
					}
					else
					{
						ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
					}
					break;
				}
			}

		}



		/**
		 * @brief		ステート内の終了処理
		 */
		virtual void End() override {
			for (auto& shot : m_Shots)
			{
				shot->SetShow(false);
				shot.reset();
			}
			m_Shots.clear();
			if (m_Effect != nullptr)
			{
				m_Effect->SetStop(true);
				m_Effect.reset();
			}
		}

	};

}