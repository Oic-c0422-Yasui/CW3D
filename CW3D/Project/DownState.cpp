#include "DownState.h"
#include "ParameterDefine.h"

ActionGame::CDownState::CDownState(Parameter param)
	: CBaseState()
	, parameter_(param)
	, currentTime_(0) {
}

void ActionGame::CDownState::Start()
{
	currentTime_ = 0;
	auto& invincible = Actor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	invincible = parameter_.endTime;
	action_ = Actor()->GetAction<CDownAction>(GetKey());
	action_->Start();
}

void ActionGame::CDownState::Execution()
{
	action_->Execution();

	if (currentTime_ < parameter_.endTime)
	{
		currentTime_ += CUtilities::GetFrameSecond();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CDownState::InputExecution()
{
}

void ActionGame::CDownState::End()
{
	action_->End();
}

void ActionGame::CDownState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CDownState::GetKey() const
{
	return STATE_KEY_DOWN;
}
