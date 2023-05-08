#include "ChaseSkillState.h"

ActionGame::CChaseSkillState::CChaseSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
	, inputKey_()
	, isDelayInput_(false)
{
}

void ActionGame::CChaseSkillState::SetUp()
{
	auto& skill = Actor()->GetSkillController()->GetSkill(SKILL_KEY_7);
	skillRef_ = std::dynamic_pointer_cast<CAdditionalSkill>(skill);

	assert(skillRef_.lock());
}

void ActionGame::CChaseSkillState::Start()
{
	action_ = Actor()->GetAction<CDropKickSkillAction>(GetKey());
	inputKey_ = skillRef_.lock()->GetButton();
	Initialize();
	if (skillRef_.lock()->IsDelayAdditional())
	{
		isDelayInput_ = true;
		skillRef_.lock()->AddInput();
	}
	else
	{
		isDelayInput_ = false;
	}
	Actor()->GetVelocity()->SetGravityScale(0.1f,
											1.0f,
											parameter_.CollideEndTime);
}

void ActionGame::CChaseSkillState::Execution()
{
	

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
	for (auto& effect : effects_)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + effect->GetOffset());
		if (currentTime_ > parameter_.CollideEndTime)
		{
			if (!effect->IsStop())
			{
				effect->SetStop(true);
			}

		}
	}

	if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}
	if (currentTime_ > parameter_.CollideEndTime)
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

	if (currentTime_ > parameter_.CollideEndTime)
	{
		SwitchFlyChangeState(STATE_KEY_IDLE, STATE_KEY_FALL);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CChaseSkillState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}
	if (!isDelayInput_)
	{
		if (Input()->IsPush(inputKey_) && !isNextInput_)
		{
			if (skillRef_.lock()->IsAdditional())
			{
				isNextInput_ = true;
				skillRef_.lock()->AddInput();
			}
		}
	}
	if (currentTime_ > parameter_.CollideEndTime)
	{
		if (Input()->IsPush(INPUT_KEY_ATTACK))
		{
			auto state = IsFly() ? STATE_KEY_JUMP_ATTACK1 : STATE_KEY_ATTACK1;

			ChangeState(state);
		}
		else if (IsPressMoveKey())
		{
			auto state = IsFly() ? STATE_KEY_FALL : STATE_KEY_MOVE;

			ChangeState(state);
		}
	}
	CAttackBaseState::InputExecution();
}

void ActionGame::CChaseSkillState::End()
{
	Actor()->GetVelocity()->SetGravityScale(1.0f, 1.0f, 0.0f);
	action_->End();
	CAttackBaseState::End();
}

void ActionGame::CChaseSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CChaseSkillState::GetKey() const
{
	return STATE_KEY_CHASE_SKILL;
}

void ActionGame::CChaseSkillState::Initialize()
{
	isStartCollide_ = false;
	CAttackBaseState::Start();
	action_->Start();
	CreateShotAABB();
	CreateEffect();
	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_7)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}
	action_->Move(Actor()->IsReverse() ? -1.0f : 1.0f);
}

