#include "JumpAttack1Action.h"

ActionGame::CJumpAttack1Action::CJumpAttack1Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CJumpAttack1Action::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	vel->SetGravity(parameter_.gravity);
	
	CBaseAction::SetRotation();
}

void ActionGame::CJumpAttack1Action::Execution()
{
}

void ActionGame::CJumpAttack1Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::CJumpAttack1Action::GetKey() const
{
	return STATE_KEY_JUMP_ATTACK1;
}
