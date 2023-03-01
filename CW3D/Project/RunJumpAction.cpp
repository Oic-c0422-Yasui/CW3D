#include "RunJumpAction.h"

ActionGame::CRunJumpAction::CRunJumpAction(BaseParameter baseParam, CMoveAction::Parameter param)
	: CMoveAction(baseParam,param)
{
}

void ActionGame::CRunJumpAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetVelocityY(parameter_.velocity.y);
	vel->SetGravity(parameter_.gravity);

	if (Transform()->IsReverse())
	{
		currentDirection_ = DIRECTION::LEFT;
	}
	else
	{
		currentDirection_ = DIRECTION::RIGHT;
	}

	CBaseAction::SetRotation();
}

void ActionGame::CRunJumpAction::Execution()
{

	CMoveAction::ChangeDirection();
}

void ActionGame::CRunJumpAction::End()
{
}


const ActionGame::ActionKeyType ActionGame::CRunJumpAction::GetKey() const
{
	return STATE_KEY_RUN_JUMP;
}
