#include "RunJumpAttack1Action.h"

ActionGame::CRunJumpAttack1Action::CRunJumpAttack1Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CRunJumpAttack1Action::Start()
{
	CBaseAction::Start();
	
	auto& vel = Velocity();
	vel->SetVelocityY(parameter_.jumpPower);
	vel->SetGravity(parameter_.gravity);
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

void ActionGame::CRunJumpAttack1Action::Execution()
{
}

void ActionGame::CRunJumpAttack1Action::End()
{
	Velocity()->SetGravity(parameter_.defaultGravity);
}

const ActionGame::ActionKeyType ActionGame::CRunJumpAttack1Action::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK1;
}
