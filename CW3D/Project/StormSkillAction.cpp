#include "StormSkillAction.h"

ActionGame::CStormSkillAction::CStormSkillAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CStormSkillAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	CBaseAction::SetRotation();
}

void ActionGame::CStormSkillAction::Execution()
{
}

void ActionGame::CStormSkillAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}

void ActionGame::CStormSkillAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CStormSkillAction::GetKey() const
{
	return STATE_KEY_STORM_SKILL;
}
