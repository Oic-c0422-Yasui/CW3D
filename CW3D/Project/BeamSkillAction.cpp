#include "BeamSkillAction.h"

ActionGame::CBeamSkillAction::CBeamSkillAction(BaseParameter baseParam,Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CBeamSkillAction::Start()
{
	CBaseAction::Start();

	Velocity()->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	
	CBaseAction::SetRotation();
}

void ActionGame::CBeamSkillAction::Execution()
{
}

void ActionGame::CBeamSkillAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CBeamSkillAction::GetKey() const
{
	return STATE_KEY_BEAM_SKILL;
}
