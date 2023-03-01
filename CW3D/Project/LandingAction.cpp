#include "LandingAction.h"

ActionGame::CLandingAction::CLandingAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CLandingAction::Start()
{
	CBaseAction::Start();

	CBaseAction::SetRotation();
}

void ActionGame::CLandingAction::Execution()
{
}

void ActionGame::CLandingAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CLandingAction::GetKey() const
{
	return STATE_KEY_LANDING;
}
