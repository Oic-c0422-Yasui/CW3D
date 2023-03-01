#include "JumpBeamSkillAction.h"

ActionGame::CJumpBeamSkillAction::CJumpBeamSkillAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CJumpBeamSkillAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetIsGravity(false);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	CBaseAction::SetRotation();
}

void ActionGame::CJumpBeamSkillAction::Execution()
{
}

void ActionGame::CJumpBeamSkillAction::End()
{
	Velocity()->SetIsGravity(true);
}

const ActionGame::ActionKeyType ActionGame::CJumpBeamSkillAction::GetKey() const
{
	return STATE_KEY_JUMP_BEAM_SKILL;
}
