#include "BeamSkillState.h"

ActionGame::BeamSkillState::BeamSkillState(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
	, m_DelayInputFlg(false)
{
}

void ActionGame::BeamSkillState::Start()
{
	m_SkillAction = Actor()->GetAction<BeamSkillAction>(GetKey());

	Initialize();
}

void ActionGame::BeamSkillState::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
		{
			shot->SetEnableCollider(true);
		}
		if (currentTime_ > m_Parameter.CollideEndFrameTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}
		}
	}
	for (auto& effect : m_pEffects)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + effect->GetOffset());
	}
	if (currentTime_ >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
	{
		collideStartFlg = true;
	}



	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		if (m_NextInputFlg)
		{
			for (auto& shot : m_pShots)
			{
				shot->SetShow(false);
			}
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

void ActionGame::BeamSkillState::InputExecution()
{
	AttackBaseState::InputExecution();
}

void ActionGame::BeamSkillState::End()
{
	m_SkillAction->End();
	AttackBaseState::End();
}

void ActionGame::BeamSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::BeamSkillState::GetKey() const
{
	return STATE_KEY_BEAM_SKILL;
}

void ActionGame::BeamSkillState::Initialize()

{

	AttackBaseState::Start();
	collideStartFlg = false;
	m_SkillAction->Start();
	m_EffectStatus = m_Parameter.EffectStatus;

	if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
	{
		
		CreateShotOBB();
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
		float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_1)->GetDamage() * 0.01f);
		shot->SetDamage(damage);
	}
}
