#include "DropKickSkillState.h"

ActionGame::CDropKickSkillState::CDropKickSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
	, inputKey_()
	, isDelayInput_(false)
{
}

void ActionGame::CDropKickSkillState::SetUp()
{
	auto& skill = Actor()->GetSkillController()->GetSkill(SKILL_KEY_4);
	m_SkillRef = std::dynamic_pointer_cast<AdditionalSkill>(skill);
	if (m_SkillRef.lock() == nullptr)
	{
		assert(m_SkillRef.lock());
	}
}

void ActionGame::CDropKickSkillState::Start()
{
	action_ = Actor()->GetAction<CDropKickSkillAction>(GetKey());
	inputKey_ = m_SkillRef.lock()->GetButton();
	Initialize();
	if (m_SkillRef.lock()->IsDelayAdditional())
	{
		isDelayInput_ = true;
		m_SkillRef.lock()->AddInput();
	}
	else
	{
		isDelayInput_ = false;
	}
}

void ActionGame::CDropKickSkillState::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
		if (currentTime_ > parameter_.CollideEndFrameTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}

		}

	}
	for (auto& effect : effects_)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + effect->GetOffset());
		if (currentTime_ > parameter_.CollideEndFrameTime)
		{
			if (!effect->IsStop())
			{
				effect->SetStop(true);
			}

		}
	}

	if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}
	if (currentTime_ > parameter_.CollideEndFrameTime)
	{
		if (isNextInput_)
		{
			for (auto& shot : shots_)
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

	CAttackBaseState::Execution();
}

void ActionGame::CDropKickSkillState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	if (!isDelayInput_)
	{
		if (Input()->IsPush(inputKey_) && !isNextInput_)
		{
			if (m_SkillRef.lock()->IsAdditional())
			{
				isNextInput_ = true;
				m_SkillRef.lock()->AddInput();
			}
		}
	}
	if (currentTime_ > parameter_.CollideEndFrameTime)
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
	CAttackBaseState::InputExecution();
}

void ActionGame::CDropKickSkillState::End()
{
	action_->End();
	CAttackBaseState::End();
}

void ActionGame::CDropKickSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CDropKickSkillState::GetKey() const
{
	return STATE_KEY_DROPKICK_SKILL;
}

void ActionGame::CDropKickSkillState::Initialize()
{
	isStartCollide_ = false;
	CAttackBaseState::Start();
	action_->Start();
	CreateShotAABB();
	CreateEffect();
	for (auto& shot : shots_)
	{
		float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_4)->GetDamage() * 0.01f);
		shot->SetDamage(damage);
	}
	action_->Move(Actor()->IsReverse() ? -1.0f : 1.0f);
}
