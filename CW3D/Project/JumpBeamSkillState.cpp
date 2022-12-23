#include "JumpBeamSkillState.h"

ActionGame::JumpBeamSkillState::JumpBeamSkillState(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
	, m_DelayInputFlg(false)
{
}

void ActionGame::JumpBeamSkillState::Start() 
{
	m_SkillAction = Actor()->GetAction<JumpBeamSkillAction>(GetKey());
	Initialize();
}

void ActionGame::JumpBeamSkillState::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
		{
			shot->SetEnableCollider(true);
		}
		if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
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
	if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
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

void ActionGame::JumpBeamSkillState::InputExecution()
{
	AttackBaseState::InputExecution();
}

void ActionGame::JumpBeamSkillState::End()
{
	m_SkillAction->End();
	AttackBaseState::End();
}

void ActionGame::JumpBeamSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::JumpBeamSkillState::GetKey() const
{
	return STATE_KEY_JUMPBEAMSKILL;
}

void ActionGame::JumpBeamSkillState::Initialize()

{

	AttackBaseState::Start();
	m_SkillAction->Start();
	collideStartFlg = false;
	m_EffectStatus = m_Parameter.EffectStatus;

	if (Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		CreateShotOBB();
		m_EffectStatus.offset = Vector3(1.7f, 0.7f, 0);
		m_EffectStatus.rotate = Vector3(MOF_ToRadian(30), MOF_ToRadian(90), 0);
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
