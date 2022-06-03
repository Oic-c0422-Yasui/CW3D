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
		bool							m_NextInputFlg;

		std::vector<ShotPtr>			m_pShots;
		std::vector<EffectPtr>			m_pEffects;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		AttackBaseState()
			: State()
			, m_FrameTime(0)
			, m_NextInputFlg(false)
		{
		}
		virtual const ShotAABB& GetCreateShotStatusAABB() { return ShotAABB(); }
		virtual const ShotSphere& GetCreateShotStatusSphere() { return ShotSphere(); }
		virtual const EffectCreateParameter& GetCreateEffectStatus() { return EffectCreateParameter(); }

		//立方体の弾を作成する
		virtual void CreateShotAABB()
		{
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			ShotAABB status = GetCreateShotStatusAABB();
			status.damage += attack;
			if (Actor()->IsReverse())
			{
				status.offset.x *= -1;
			}

			m_pShots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
		}
		//球体の弾を作成する
		virtual void CreateShotSphere()
		{
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			ShotSphere status = GetCreateShotStatusSphere();
			status.damage += attack;
			if (Actor()->IsReverse())
			{
				status.offset.x *= -1;
			}

			m_pShots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
		}

		//エフェクトを作成する
		virtual void CreateEffect()
		{
			EffectCreateParameter status = GetCreateEffectStatus();
			
			if (Actor()->IsReverse())
			{
				status.offset.x *= -1;
				if (status.rotate.y == MOF_ToRadian(360))
				{
					status.rotate.y = MOF_ToRadian(180);
				}
				else
				{
					status.rotate.y *= -1;
				}
			}
			m_pEffects.push_back(EffectControllerInstance.Play(status.name, Actor()->GetPosition(),status));
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		virtual void Start() override {
			m_FrameTime = 0;
			m_NextInputFlg = false;
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);

			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);
			}
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
			for (auto& shot : m_pShots)
			{
				shot->SetShow(false);
				shot.reset();
			}
			m_pShots.clear();
			for (auto& effect : m_pEffects)
			{
				effect->SetStop(true);
				effect.reset();
			}
			m_pEffects.clear();
		}

	};

}