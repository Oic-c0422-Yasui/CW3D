#include "Attack2Action.h"

ActionGame::CAttack2Action::CAttack2Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CAttack2Action::Start()
{

	CBaseAction::Start();
	
	auto& vel = Velocity();
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	if (Transform()->IsReverse())
	{
		vel->SetVelocity(Vector3(-parameter_.velocity.x, parameter_.velocity.y, parameter_.velocity.z));
	}
	else
	{
		vel->SetVelocity(Vector3(parameter_.velocity.x, parameter_.velocity.y, parameter_.velocity.z));
	}

	CBaseAction::SetRotation();
}

void ActionGame::CAttack2Action::Execution()
{
}

void ActionGame::CAttack2Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::CAttack2Action::GetKey() const
{
	return STATE_KEY_ATTACK2;
}
