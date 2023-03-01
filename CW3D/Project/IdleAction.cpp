#include "IdleAction.h"

ActionGame::CIdleAction::CIdleAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CIdleAction::Start()
{
	CBaseAction::Start();
	
	auto& vel = Velocity();
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	CBaseAction::SetRotation();
}

void ActionGame::CIdleAction::Execution()
{
}

void ActionGame::CIdleAction::End()
{
}

void ActionGame::CIdleAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}

void ActionGame::CIdleAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::CIdleAction::GetKey() const
{
	return STATE_KEY_IDLE;
}
