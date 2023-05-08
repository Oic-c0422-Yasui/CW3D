#include "ImpactSkillState.h"

ActionGame::CImpactSkillState::CImpactSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CImpactSkillState::Start()
{
	fallAction_ = Actor()->GetAction<CFallAction>(GetKey());
	moveAction_ = Actor()->GetAction<CAttack1Action>(GetKey() + STATE_KEY_ATTACK1);

	isStartCollide_ = false;
	isLanding_ = false;
	CAttackBaseState::Start();
	fallAction_->Start();
	moveAction_->Start();

	SetArmorLevel(parameter_.armorLevel);

	CreateShotAABB();

	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_6)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}

	
}

void ActionGame::CImpactSkillState::Execution()
{

	fallAction_->Execution();

	if (IsFly())
	{
		return;
	}
	if (!isLanding_)
	{
		CreateEffect();
		isLanding_ = true;
	}


	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
		if (currentTime_ > parameter_.CollideEndTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}
		}

	}
	if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion() &&
		currentTime_ > parameter_.EndTime)
	{
		ChangeState(STATE_KEY_IDLE);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CImpactSkillState::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CImpactSkillState::End()
{
	fallAction_->End();
	moveAction_->End();
	CAttackBaseState::End();
}

void ActionGame::CImpactSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CImpactSkillState::GetKey() const
{
	return STATE_KEY_IMPACT_SKILL;
}
