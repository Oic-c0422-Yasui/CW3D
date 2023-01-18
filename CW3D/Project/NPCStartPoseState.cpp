#include "NPCStartPoseState.h"

ActionGame::NPCStartPoseState::NPCStartPoseState()
	: State()
{
}

void ActionGame::NPCStartPoseState::Start()
{
	m_Action = Actor()->GetAction<NPCStartPoseAction>(GetKey());
	m_Action->Start();
	
}

void ActionGame::NPCStartPoseState::Execution()
{

	m_Action->Execution();
	
	if (m_Action->IsEndAnim())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	
}

void ActionGame::NPCStartPoseState::InputExecution()
{
}

void ActionGame::NPCStartPoseState::End()
{
	m_Action->End();
}

void ActionGame::NPCStartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::NPCStartPoseState::GetKey() const
{
	return STATE_KEY_NPC_STARTPOSE;
}
