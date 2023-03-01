#include "Attack1Action.h"

ActionGame::CAttack1Action::CAttack1Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CAttack1Action::Start()
{
	CBaseAction::Start();
	
	auto& vel = Velocity();
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	if (Transform()->IsReverse())
	{
		vel->SetVelocityX(-parameter_.velocity.x);
	}
	else
	{
		vel->SetVelocityX(parameter_.velocity.x);
	}

	CBaseAction::SetRotation();
}

void ActionGame::CAttack1Action::Execution()
{
}

void ActionGame::CAttack1Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::CAttack1Action::GetKey() const
{
	return STATE_KEY_ATTACK1;
}
