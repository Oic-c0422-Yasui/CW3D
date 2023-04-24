#include "FallState.h"

ActionGame::CFallState::CFallState()
	: CBaseState()
{
}

void ActionGame::CFallState::Start() 
{
	action_ = Actor()->GetAction<CFallAction>(GetKey());
	action_->Start();

}

void ActionGame::CFallState::Execution()
{
	action_->Execution();
	// 着地状態への移行
	if (!IsFly())
	{
		ChangeState(STATE_KEY_LANDING);
	}
}

void ActionGame::CFallState::InputExecution()
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
		ChangeState(STATE_KEY_JUMP_ATTACK1);
	}

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	ChangeSkillState();

}

void ActionGame::CFallState::End()
{
}

void ActionGame::CFallState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CFallState::GetKey() const
{
	return STATE_KEY_FALL;
}