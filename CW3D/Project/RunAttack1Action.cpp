#include "RunAttack1Action.h"

ActionGame::CRunAttack1Action::CRunAttack1Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CRunAttack1Action::Start()
{
	CBaseAction::Start();

	Velocity()->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	
	CBaseAction::SetRotation();
}

void ActionGame::CRunAttack1Action::Execution()
{
}

void ActionGame::CRunAttack1Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::CRunAttack1Action::GetKey() const
{
	return STATE_KEY_RUN_ATTACK1;
}
