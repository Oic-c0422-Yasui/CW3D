#include "JumpBeamSkillState.h"

ActionGame::CJumpBeamSkillState::CJumpBeamSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
	, isDelayInput_(false)
{
}

void ActionGame::CJumpBeamSkillState::Start() 
{
	action_ = Actor()->GetAction<CJumpBeamSkillAction>(GetKey());
	Initialize();
}

void ActionGame::CJumpBeamSkillState::Execution()
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
	}
	if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		if (isNextInput_)
		{
			for (auto& shot : shots_)
			{
				shot->SetShow(false);
			}
			Initialize();
		}
		else
		{
			auto state = IsFly() ? STATE_KEY_FALL : STATE_KEY_IDLE;

			ChangeState(state);
		}
	}
	CAttackBaseState::Execution();
}

void ActionGame::CJumpBeamSkillState::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CJumpBeamSkillState::End()
{
	action_->End();
	CAttackBaseState::End();
}

void ActionGame::CJumpBeamSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CJumpBeamSkillState::GetKey() const
{
	return STATE_KEY_JUMP_BEAM_SKILL;
}

void ActionGame::CJumpBeamSkillState::Initialize()

{

	CAttackBaseState::Start();
	action_->Start();
	isStartCollide_ = false;
	effectStatus_ = parameter_.EffectStatus;

	if (Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		CreateShotOBB();
		effectStatus_.offset = Vector3(1.7f, 0.7f, 0);
		effectStatus_.rotate = Vector3(MOF_ToRadian(30), MOF_ToRadian(90), 0);
		CreateEffect();

	}
	else
	{
		CreateShotAABB();
		CreateEffect();

	}
	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_1)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}
}
