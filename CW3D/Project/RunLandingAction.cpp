#include "RunLandingAction.h"

ActionGame::CRunLandingAction::CRunLandingAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CRunLandingAction::Start()
{
	CBaseAction::Start();

	CBaseAction::SetRotation();
}

void ActionGame::CRunLandingAction::Execution()
{
}

void ActionGame::CRunLandingAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CRunLandingAction::GetKey() const
{
	return STATE_KEY_RUN_LANDING;
}
