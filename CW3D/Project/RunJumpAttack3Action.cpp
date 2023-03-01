#include "RunJumpAttack3Action.h"

ActionGame::CRunJumpAttack3Action::CRunJumpAttack3Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CRunJumpAttack3Action::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetVelocityY(parameter_.jumpPower);
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

void ActionGame::CRunJumpAttack3Action::Execution()
{
	if (Transform()->IsReverse())
	{
		Velocity()->SetVelocity(Vector3(-0.1f, 0, 0));
	}
	else
	{
		Velocity()->SetVelocity(Vector3(0.1f, 0, 0));
	}
}

void ActionGame::CRunJumpAttack3Action::End()
{
	Velocity()->SetGravity(parameter_.defaultGravity);
}

void ActionGame::CRunJumpAttack3Action::Jump()
{
	Velocity()->SetVelocityY(parameter_.jumpPower);
}

const ActionGame::ActionKeyType ActionGame::CRunJumpAttack3Action::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK3;
}