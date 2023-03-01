#include "RunState.h"

ActionGame::CRunState::CRunState()
	: CState() 
{
}

void ActionGame::CRunState::Start()
{
	action_ = Actor()->GetAction<CMoveAction>(STATE_KEY_RUN);
	if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(false);
	}
	else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(true);
	}
	action_->Start();
}

void ActionGame::CRunState::Execution()
{
	action_->Execution();
}

void ActionGame::CRunState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	//左右で移動
	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL),
							-(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}
	else
	{
		ChangeState(STATE_KEY_IDLE, STATE_KEY_MOVE);
	}

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_RUN_ATTACK1, GetKey());
	}

	if (Input()->IsPush(INPUT_KEY_JUMP))
	{
		ChangeState(STATE_KEY_RUN_JUMP, GetKey());
	}

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	for (size_t i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		auto& skill = Actor()->GetSkillController()->GetSkill(i);
		if (!skill->IsCanUse() || skill->GetState() == NULL)
		{
			continue;
		}
		if (Input()->IsPush(skill->GetButton()))
		{
			skill->Start();
			ChangeState(skill->GetState(), GetKey());
			break;
		}
	}
}

void ActionGame::CRunState::End()
{
}

void ActionGame::CRunState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunState::GetKey() const
{
	return STATE_KEY_RUN;
}
