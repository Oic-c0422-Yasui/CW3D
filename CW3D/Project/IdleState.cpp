#include "IdleState.h"

ActionGame::CIdleState::CIdleState(Parameter param)
	: CBaseState()
	, time_(0.0f)
	, parameter_(param)
{
}

void ActionGame::CIdleState::Start()
{
	action_ = Actor()->GetAction<CIdleAction>(GetKey());
	time_ = 0.0f;
	action_->Start();
}

void ActionGame::CIdleState::Execution()
{
	if (time_ < parameter_.idleTime)
	{
		time_ += CUtilities::GetFrameSecond();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE_MOTION);
	}
}

void ActionGame::CIdleState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}

	if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
	{
		ChangeState(STATE_KEY_RUN);
	}
	//キーボードでの移動
	else if (IsPressMoveKey())
	{
		ChangeState(STATE_KEY_MOVE);
	}

	if (Input()->IsPush(INPUT_KEY_JUMP))
	{
		ChangeState(STATE_KEY_JUMP, STATE_KEY_MOVE);
	}

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1, STATE_KEY_MOVE);
	}

	
	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	ChangeSkillState();

}

void ActionGame::CIdleState::End()
{
}

void ActionGame::CIdleState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CIdleState::GetKey() const
{
	return STATE_KEY_IDLE;
}

