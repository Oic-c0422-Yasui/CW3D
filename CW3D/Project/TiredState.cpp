#include "TiredState.h"

ActionGame::CTiredState::CTiredState(Parameter param)
	: CBaseState()
	, time_(0.0f)
	, parameter_(param)
{
}

void ActionGame::CTiredState::Start()
{
	action_ = Actor()->GetAction<CIdleAction>(GetKey());
	time_ = 0.0f;
	action_->Start();
}

void ActionGame::CTiredState::Execution()
{
	if (time_ < parameter_.Time)
	{
		time_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	}
	else
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CTiredState::InputExecution()
{
}

void ActionGame::CTiredState::End()
{
}

void ActionGame::CTiredState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CTiredState::GetKey() const
{
	return STATE_KEY_TIRED;
}
