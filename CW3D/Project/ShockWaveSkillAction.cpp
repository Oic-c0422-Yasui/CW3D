#include "ShockWaveSkillAction.h"

ActionGame::CShockWaveSkillAction::CShockWaveSkillAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CShockWaveSkillAction::Start()
{
	CBaseAction::Start();
	
	//d—ÍOFF
	auto& vel = Velocity();
	vel->SetIsGravity(false);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	CBaseAction::SetRotation();
}

void ActionGame::CShockWaveSkillAction::Execution()
{
}

void ActionGame::CShockWaveSkillAction::End()
{
	//d—ÍON
	Velocity()->SetIsGravity(true);
}

const ActionGame::ActionKeyType ActionGame::CShockWaveSkillAction::GetKey() const
{
	return STATE_KEY_SHOCKWAVE_SKILL;
}
