#include "RunJumpAttack2Action.h"

ActionGame::CRunJumpAttack2Action::CRunJumpAttack2Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CRunJumpAttack2Action::Start()
{
	CBaseAction::Start();
	
	auto& vel = Velocity();
	vel->SetVelocityY(parameter_.jumpPower);
	vel->SetGravity(parameter_.gravity);

	if (Transform()->IsReverse())
	{
		Velocity()->SetVelocityX(-parameter_.velocity.x);
	}
	else
	{
		Velocity()->SetVelocityX(parameter_.velocity.x);
	}

	CBaseAction::SetRotation();
}

void ActionGame::CRunJumpAttack2Action::Execution()
{
}

void ActionGame::CRunJumpAttack2Action::End()
{
	Velocity()->SetGravity(parameter_.defaultGravity);
}

const ActionGame::ActionKeyType ActionGame::CRunJumpAttack2Action::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK2;
}
