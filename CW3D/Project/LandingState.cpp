#include "LandingState.h"

ActionGame::CLandingState::CLandingState()
	: CBaseState()
{
}

void ActionGame::CLandingState::Start()
{
	action_ = Actor()->GetAction<CLandingAction>(GetKey());
	action_->Start();

}

void ActionGame::CLandingState::Execution() 
{
	action_->Execution();
	// 落下状態への移行
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CLandingState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}

	//左右で移動
	if (IsPressMoveKey())
	{
		ChangeState(STATE_KEY_MOVE);
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1);
	}

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	ChangeSkillState();

}

void ActionGame::CLandingState::End()
{
}

void ActionGame::CLandingState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CLandingState::GetKey() const
{
	return STATE_KEY_LANDING;
}
