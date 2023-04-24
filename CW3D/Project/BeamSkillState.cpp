#include "BeamSkillState.h"

ActionGame::CBeamSkillState::CBeamSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
	, isDelayInput_(false)
{
}

void ActionGame::CBeamSkillState::Start()
{
	action_ = Actor()->GetAction<CBeamSkillAction>(GetKey());

	Initialize();
}

void ActionGame::CBeamSkillState::Execution()
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

void ActionGame::CBeamSkillState::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CBeamSkillState::End()
{
	action_->End();
	CAttackBaseState::End();
}

void ActionGame::CBeamSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CBeamSkillState::GetKey() const
{
	return STATE_KEY_BEAM_SKILL;
}

void ActionGame::CBeamSkillState::Initialize()
{

	CAttackBaseState::Start();
	isStartCollide_ = false;
	action_->Start();
	effectStatus_ = parameter_.EffectStatus;

	if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
	{
		CreateShotOBB();
		effectStatus_.offset = Vector3(1.7f, 1.8f, 0);
		effectStatus_.rotate = Vector3(MOF_ToRadian(-30), MOF_ToRadian(90), 0);
		CreateEffect();
	}
	else
	{
		CreateShotAABB();
		CreateEffect();
	}
	for (auto& shot : shots_)
	{
		auto skillDamage = Actor() -> GetSkillController()->GetSkill(SKILL_KEY_1)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}
}
