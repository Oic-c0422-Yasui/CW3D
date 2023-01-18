#include "DropKickSkillState.h"

ActionGame::DropKickSkillState::DropKickSkillState(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
	, m_Key()
	, m_DelayInputFlg(false)
{
}

void ActionGame::DropKickSkillState::SetUp()
{
	auto& skill = Actor()->GetSkillController()->GetSkill(SKILL_KEY_4);
	m_SkillRef = std::dynamic_pointer_cast<AdditionalSkill>(skill);
	if (m_SkillRef.lock() == nullptr)
	{
		assert(m_SkillRef.lock());
	}
}

void ActionGame::DropKickSkillState::Start()
{
	m_SkillAction = Actor()->GetAction<DropKickSkillAction>(GetKey());
	m_Key = m_SkillRef.lock()->GetButton();
	Initialize();
	if (m_SkillRef.lock()->IsDelayAdditional())
	{
		m_DelayInputFlg = true;
		m_SkillRef.lock()->AddInput();
	}
	else
	{
		m_DelayInputFlg = false;
	}
}

void ActionGame::DropKickSkillState::Execution()
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

void ActionGame::DropKickSkillState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	if (!m_DelayInputFlg)
	{
		if (Input()->IsPush(m_Key) && !m_NextInputFlg)
		{
			if (m_SkillRef.lock()->IsAdditional())
			{
				m_NextInputFlg = true;
				m_SkillRef.lock()->AddInput();
			}
		}
	}
	if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
	{
		if (Input()->IsPush(INPUT_KEY_ATTACK))
		{
			if (Actor()->GetTransform()->GetPositionY() > 0.0f)
			{
				ChangeState(STATE_KEY_JUMP_ATTACK1);
			}
			else
			{
				ChangeState(STATE_KEY_ATTACK1);
			}
		}
		else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) || Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
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

void ActionGame::DropKickSkillState::End()
{
	m_SkillAction->End();
	AttackBaseState::End();
}

void ActionGame::DropKickSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::DropKickSkillState::GetKey() const
{
	return STATE_KEY_DROPKICK_SKILL;
}

void ActionGame::DropKickSkillState::Initialize()
{
	collideStartFlg = false;
	AttackBaseState::Start();
	m_SkillAction->Start();
	CreateShotAABB();
	CreateEffect();
	for (auto& shot : m_pShots)
	{
		float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_4)->GetDamage() * 0.01f);
		shot->SetDamage(damage);
	}
	m_SkillAction->Move(Actor()->IsReverse() ? -1.0f : 1.0f);
}
