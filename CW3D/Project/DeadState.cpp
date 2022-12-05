#include "DeadState.h"

ActionGame::DeadState::DeadState()
	: State()
{
}

void ActionGame::DeadState::Start()
{
	m_DeadAction = Actor()->GetAction<DeadAction>(GetKey());
	m_DeadAction->Start();
}

void ActionGame::DeadState::Execution()
{
	m_DeadAction->Execution();
}

void ActionGame::DeadState::InputExecution()
{
}

void ActionGame::DeadState::End()
{
	m_DeadAction->End();
}

void ActionGame::DeadState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::DeadState::GetKey() const
{
	return STATE_KEY_DEAD;
}
