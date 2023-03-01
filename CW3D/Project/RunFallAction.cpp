#include "FallAction.h"
#include "RunFallAction.h"


ActionGame::CRunFallAction::CRunFallAction(BaseParameter baseParam, Parameter param)
	: CMoveAction(baseParam,param)
{
}

void ActionGame::CRunFallAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetGravity(parameter_.gravity);

	CMoveAction::InitDirection();

	CBaseAction::SetRotation();
}

void ActionGame::CRunFallAction::Execution()
{

	CMoveAction::ChangeDirection();
}

void ActionGame::CRunFallAction::End()
{
}

void ActionGame::CRunFallAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::CRunFallAction::GetKey() const
{
	return STATE_KEY_RUN_FALL;
}

