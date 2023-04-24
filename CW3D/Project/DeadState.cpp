#include "DeadState.h"

ActionGame::CDeadState::CDeadState()
	: CBaseState()
{
}

void ActionGame::CDeadState::Start()
{
	action_ = Actor()->GetAction<CDeadAction>(GetKey());
	action_->Start();
}

void ActionGame::CDeadState::Execution()
{
	action_->Execution();
}

void ActionGame::CDeadState::InputExecution()
{
}

void ActionGame::CDeadState::End()
{
	action_->End();
}

void ActionGame::CDeadState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CDeadState::GetKey() const
{
	return STATE_KEY_DEAD;
}
