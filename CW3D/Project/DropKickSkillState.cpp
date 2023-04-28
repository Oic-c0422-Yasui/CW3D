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
	skillRef_ = std::dynamic_pointer_cast<CAdditionalSkill>(skill);

	assert(skillRef_.lock());
}

void ActionGame::CDropKickSkillState::Start()
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
	/*if (currentTime_ > parameter_.CollideEndFrameTime)
	{
		if (isNextInput_)
		{
			for (auto& shot : shots_)
			{
				shot->SetShow(false);
			}
			Initialize();
			return;
		}
	}*/

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		auto state = IsFly() ? STATE_KEY_FALL : STATE_KEY_IDLE;

		ChangeState(state);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CDropKickSkillState::InputExecution()
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
				for (auto& shot : shots_)
				{
					shot->SetShow(false);
				}
				Initialize();
				return;

			}
		}
	}
	if (currentTime_ > parameter_.CollideEndFrameTime)
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

	SetArmorLevel(parameter_.armorLevel);

	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_4)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}
	action_->Move(Actor()->IsReverse() ? -1.0f : 1.0f);
}
