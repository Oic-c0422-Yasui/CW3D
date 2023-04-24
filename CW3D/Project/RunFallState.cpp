#include "RunFallState.h"

ActionGame::CRunFallState::CRunFallState()
	: CBaseState()
{
}

void ActionGame::CRunFallState::Start()
{
	action_ = Actor()->GetAction<CRunFallAction>(GetKey());
	action_->Start();

}

void ActionGame::CRunFallState::Execution()
{
	action_->Execution();
	// 着地状態への移行
	if (!IsFly())
	{
		ChangeState(STATE_KEY_RUN_LANDING);
	}
}

void ActionGame::CRunFallState::InputExecution()
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

void ActionGame::CRunFallState::End()
{
}

void ActionGame::CRunFallState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunFallState::GetKey() const
{
	return STATE_KEY_RUN_FALL;
}
