#pragma once


#include	"AttackBaseState.h"
#include	"DropKickSkillAction.h"


namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class DropKickSkillState : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		DropKickSkillActionPtr			m_SkillAction;

		bool collideStartFlg;
		bool m_DelayInputFlg;
		std::string m_Key;

		AdditionalWeakSKillPtr m_Skill;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DropKickSkillState(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideStartFlg(false)
			, m_Key()
			, m_DelayInputFlg(false)
		{
		}


		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }

		/**
		 * @brief		ステートの初期化時処理
		 */
		void SetUp() override
		{
			auto& skill = Actor()->GetSkillController()->GetSkill(SKILL_KEY_DROPKICK);
			m_Skill = std::dynamic_pointer_cast<CAdditionalSkill>(skill);
			if (m_Skill.lock() == nullptr)
			{
				assert(m_Skill.lock());
			}
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<DropKickSkillAction>(GetKey());
			m_Key = m_Skill.lock()->GetButton();
			Initialize();
			if (m_Skill.lock()->IsDelayAdditional())
			{
				m_DelayInputFlg = true;
				m_Skill.lock()->AddInput();
			}
			else
			{
				m_DelayInputFlg = false;
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
				if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
				{
					if (!effect->IsStop())
					{
						effect->SetStop(true);
					}

				}
			}

			if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
			{
				collideStartFlg = true;
			}
			if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
			{
				if (m_NextInputFlg)
				{
					for (auto& shot : m_pShots)
					{
						shot->SetShow(false);
					}
					Initialize();
				}
			}

			if (Actor()->GetAnimationState()->IsEndMotion())
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

			AttackBaseState::Execution();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			if (!m_DelayInputFlg)
			{
				if (Input()->IsPush(m_Key) && !m_NextInputFlg)
				{
					if (m_Skill.lock()->IsAdditional())
					{
						m_NextInputFlg = true;
						m_Skill.lock()->AddInput();
					}
				}
			}
			if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
			{
				if (Input()->IsPush(INPUT_KEY_ATTACK))
				{
					if (Actor()->GetTransform()->GetPositionY() > 0.0f)
					{
						ChangeState(STATE_KEY_JUMPATTACK1);
					}
					else
					{
						ChangeState(STATE_KEY_ATTACK1);
					}
				}
				else if(Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) || Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
					Input()->IsNegativePress(INPUT_KEY_VERTICAL) || Input()->IsPress(INPUT_KEY_VERTICAL))
				{
					if (Actor()->GetTransform()->GetPositionY() > 0.0f)
					{
						ChangeState(STATE_KEY_FALL);
					}
					else
					{
						ChangeState(STATE_KEY_MOVE);
					}
				}
			}
			AttackBaseState::InputExecution();
		}

		void Initialize()
		{
			collideStartFlg = false;
			AttackBaseState::Start();
			m_SkillAction->Start();
			CreateShotAABB();
			CreateEffect();
			for (auto& shot : m_pShots)
			{
				float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_DROPKICK)->GetDamage() * 0.01f);
				shot->SetDamage(damage);
			}
			m_SkillAction->Move(Actor()->IsReverse() ? -1.0f : 1.0f);
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
			return STATE_KEY_DROPKICKSKILL;
		}
	};

}