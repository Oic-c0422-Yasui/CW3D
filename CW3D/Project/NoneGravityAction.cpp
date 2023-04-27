#include "NoneGravityAction.h"

ActionGame::CNoneGravityAction::CNoneGravityAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CNoneGravityAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetIsGravity(false);
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	CBaseAction::SetRotation();
}

void ActionGame::CNoneGravityAction::Execution()
{
}

void ActionGame::CNoneGravityAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}

void ActionGame::CNoneGravityAction::End()
{
	Velocity()->SetIsGravity(true);
}

const ActionGame::ActionKeyType ActionGame::CNoneGravityAction::GetKey() const
{
	return STATE_KEY_JUMP_STORM_SKILL;
}
