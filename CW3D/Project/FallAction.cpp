#include "FallAction.h"

ActionGame::CFallAction::CFallAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CFallAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetMaxVelocity(parameter_.maxVelocty.x, parameter_.maxVelocty.z);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetGravity(parameter_.gravity);

	CBaseAction::SetRotation();
}

void ActionGame::CFallAction::Execution()
{
}

void ActionGame::CFallAction::End()
{
}

void ActionGame::CFallAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}

void ActionGame::CFallAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::CFallAction::GetKey() const
{
	return STATE_KEY_FALL;
}
