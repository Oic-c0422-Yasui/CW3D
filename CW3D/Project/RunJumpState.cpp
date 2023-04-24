#include "RunJumpState.h"

ActionGame::CRunJumpState::CRunJumpState()
	: CBaseState()
{
}

void ActionGame::CRunJumpState::Start()
{
	action_ = Actor()->GetAction<CRunJumpAction>(GetKey());
	action_->Start();

}

void ActionGame::CRunJumpState::Execution()
{
	action_->Execution();
	// 落下状態への移行
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
	{
		ChangeState(STATE_KEY_RUN_FALL);
	}
}

void ActionGame::CRunJumpState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}
	//左右で移動

	if (IsPressMoveKey())
	{
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), 
							-(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_RUN_JUMP_ATTACK1);
	}

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	ChangeSkillState();

}

void ActionGame::CRunJumpState::End()
{
}

void ActionGame::CRunJumpState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunJumpState::GetKey() const
{
	return STATE_KEY_RUN_JUMP;
}

