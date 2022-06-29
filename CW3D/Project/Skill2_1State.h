#pragma once


#include	"AttackBaseState.h"
#include	"Skill2_1Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Skill2_1State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB AABBShotStatus;
			ShotSphere SphereShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		Skill2_1ActionPtr			m_SkillAction;

		std::string m_Key;

		AdditionalSKillPtr m_AddSkill;

		bool collideStartFlg;

		ShotSphere m_ShotStatusSphere;

		EffectCreateParameter m_EffectStatus;

		
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Skill2_1State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideStartFlg(false)
			, m_Key()
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.AABBShotStatus; }
		const ShotSphere& GetCreateShotStatusSphere() override { return m_ShotStatusSphere; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_EffectStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill2_1Action>(GetKey());
			Initialize();
			m_AddSkill = std::dynamic_pointer_cast<CAdditionalSkill>(Actor()->GetSkillController()->GetSkill(SKILL_KEY_1));
			if (m_AddSkill != nullptr)
			{
				m_Key = m_AddSkill->GetButton();
			}
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {

			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
				{
					shot->SetCollideFlg(true);
				}
				if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
				{
					if (shot->GetCollideFlg())
					{
						shot->SetCollideFlg(false);
					}
				}
			}
			for (auto& effect : m_pEffects)
			{
				EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + effect->GetOffset());
			}
			if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
			{
				collideStartFlg = true;
			}
			


			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				if (m_NextInputFlg)
				{
					Initialize();
				}
				else
				{
					if (Actor()->GetTransform()->GetPositionY() > 0)
					{
						ChangeState(STATE_KEY_FALL);
					}
					else
					{
						ChangeState(STATE_KEY_IDLE);
					}
				}
			}
			AttackBaseState::Execution();

		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {

			if (m_AddSkill != nullptr)
			{
				if (Input()->IsPush(m_Key))
				{
					if (m_AddSkill->IsAdditional())
					{
						m_NextInputFlg = true;
					}
				}
			}

			AttackBaseState::InputExecution();
		}



		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			m_SkillAction->End();
			AttackBaseState::End();

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
			return STATE_KEY_SKILL2_1;
		}


		void Initialize()
		{
			

			AttackBaseState::Start();
			collideStartFlg = false;
			m_SkillAction->Start();
			m_EffectStatus = m_Parameter.EffectStatus;
			m_ShotStatusSphere = m_Parameter.SphereShotStatus;
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				float rad = MOF_ToRadian(-30);
				Vector3 direction(cos(rad), sin(rad), 0);
				int shotCount = 3;
				for (int i = 0; i < shotCount; i++)
				{
					m_ShotStatusSphere.offset = Vector3(((2 + (4 * i)) * direction.x), 0.7f + -((2 + (4 * i)) * direction.y), 0);
					CreateShotSphere();
				}

				m_EffectStatus.offset = Vector3(1.7f, 1.8f, 0);
				m_EffectStatus.rotate = Vector3(MOF_ToRadian(-30), MOF_ToRadian(90), 0);
				CreateEffect();

			}
			else
			{
				CreateShotAABB();
				CreateEffect();

			}
			for (auto& shot : m_pShots)
			{
				float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetDamage() * 0.01f);
				shot->SetDamage(damage);
			}
		}
	};

}