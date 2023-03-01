#include "JumpState.h"

ActionGame::CJumpState::CJumpState()
	: CState()
{
}

void ActionGame::CJumpState::Start()
{
	action_ = Actor()->GetAction<CJumpAction>(GetKey());
	action_->Start();

}

void ActionGame::CJumpState::Execution()
{
	action_->Execution();
	// 落下状態への移行
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
	{
		ChangeState(STATE_KEY_FALL);
	}
}

void ActionGame::CJumpState::InputExecution()
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
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_JUMP_ATTACK1);
	}

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		if (!Actor()->GetSkillController()->GetSkill(i)->IsCanUse() || Actor()->GetSkillController()->GetSkill(i)->GetFlyState() == NULL)
		{
			continue;
		}
		if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
		{

			Actor()->GetSkillController()->GetSkill(i)->Start();
			ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
			break;
		}
	}

}

void ActionGame::CJumpState::End()
{
}

void ActionGame::CJumpState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CJumpState::GetKey() const
{
	return STATE_KEY_JUMP;
}
