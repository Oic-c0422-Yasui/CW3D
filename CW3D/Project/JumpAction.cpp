#include "JumpAction.h"

ActionGame::CJumpAction::CJumpAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CJumpAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetVelocityY(parameter_.jumpPower);
	vel->SetGravity(parameter_.gravity);

	CBaseAction::SetRotation();
}

void ActionGame::CJumpAction::Execution()
{
}

void ActionGame::CJumpAction::End()
{
}

void ActionGame::CJumpAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}

void ActionGame::CJumpAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::CJumpAction::GetKey() const
{
	return STATE_KEY_JUMP;
}
