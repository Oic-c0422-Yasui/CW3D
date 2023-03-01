#include "EscapeAction.h"
#include "ParameterDefine.h"

ActionGame::CEscapeAction::CEscapeAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CEscapeAction::Start()
{
	CBaseAction::Start();
	
	Velocity()->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	
	CBaseAction::SetRotation();
}

void ActionGame::CEscapeAction::Execution()
{
}

void ActionGame::CEscapeAction::End()
{
	EndThrough();
}

void ActionGame::CEscapeAction::Move(float x, float z)
{
	Velocity()->SetVelocityX(x * parameter_.velocity.x);
	Velocity()->SetVelocityZ(z * parameter_.velocity.z);
}

void ActionGame::CEscapeAction::StartThrough()
{
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = true;
}

void ActionGame::CEscapeAction::EndThrough()
{
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = false;
}

const ActionGame::ActionKeyType ActionGame::CEscapeAction::GetKey() const
{
	return STATE_KEY_ESCAPE;
}
