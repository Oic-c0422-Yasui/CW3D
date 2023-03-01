#include "IdleMotionAction.h"

ActionGame::IdleMotionAction::IdleMotionAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::IdleMotionAction::Start()
{
	CBaseAction::Start();

	CBaseAction::SetRotation();
}

void ActionGame::IdleMotionAction::Execution()
{
}

void ActionGame::IdleMotionAction::End()
{
}

void ActionGame::IdleMotionAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}


const ActionGame::ActionKeyType ActionGame::IdleMotionAction::GetKey() const
{
	return STATE_KEY_IDLE_MOTION;
}
