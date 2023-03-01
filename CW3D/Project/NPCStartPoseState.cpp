#include "NPCStartPoseState.h"

ActionGame::CNPCStartPoseState::CNPCStartPoseState()
	: CState()
{
}

void ActionGame::CNPCStartPoseState::Start()
{
	action_ = Actor()->GetAction<CNPCStartPoseAction>(GetKey());
	action_->Start();
	
}

void ActionGame::CNPCStartPoseState::Execution()
{

	action_->Execution();
	
	if (action_->IsEndAnimation())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	
}

void ActionGame::CNPCStartPoseState::InputExecution()
{
}

void ActionGame::CNPCStartPoseState::End()
{
	action_->End();
}

void ActionGame::CNPCStartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CNPCStartPoseState::GetKey() const
{
	return STATE_KEY_NPC_STARTPOSE;
}
