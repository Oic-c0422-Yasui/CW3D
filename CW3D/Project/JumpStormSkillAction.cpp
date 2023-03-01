#include "JumpStormSkillAction.h"

ActionGame::CJumpStormSkillAction::CJumpStormSkillAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CJumpStormSkillAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetIsGravity(false);
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	CBaseAction::SetRotation();
}

void ActionGame::CJumpStormSkillAction::Execution()
{
}

void ActionGame::CJumpStormSkillAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}

void ActionGame::CJumpStormSkillAction::End()
{
	Velocity()->SetIsGravity(true);
}

const ActionGame::ActionKeyType ActionGame::CJumpStormSkillAction::GetKey() const
{
	return STATE_KEY_JUMP_STORM_SKILL;
}
