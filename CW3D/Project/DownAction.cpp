#include "DownAction.h"

ActionGame::CDownAction::CDownAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CDownAction::Start()
{
	CBaseAction::Start();

	Velocity()->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
}

void ActionGame::CDownAction::Execution()
{
}

void ActionGame::CDownAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CDownAction::GetKey() const
{
	return STATE_KEY_DOWN;
}
