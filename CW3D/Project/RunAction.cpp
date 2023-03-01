#include "RunAction.h"

ActionGame::CRunAction::CRunAction(BaseParameter baseParam, Parameter param)
	: CMoveAction(baseParam,param)
{
}

void ActionGame::CRunAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	InitDirection();

	CBaseAction::SetRotation();
}

void ActionGame::CRunAction::Execution()
{

	auto& velocity = Velocity();
	bool isReverse = Transform()->IsReverse();

	//¶‰EŒü‚«•ÏX
	if (velocity->GetVelocityX() < 0 && !isReverse)
	{
		Transform()->SetReverse(true);
	}
	else if (velocity->GetVelocityX() > 0 && isReverse)
	{
		Transform()->SetReverse(false);
	}

	ChangeDirection();
}

void ActionGame::CRunAction::End()
{
}

void ActionGame::CRunAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::CRunAction::GetKey() const
{
	return STATE_KEY_RUN;
}
