#include "DropKickSkillAction.h"

ActionGame::CDropKickSkillAction::CDropKickSkillAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CDropKickSkillAction::Start()
{
	CBaseAction::Start();


	auto& vel = Velocity();
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetVelocityY(parameter_.jumpPower);
	vel->SetGravity(parameter_.gravity);
	
	CBaseAction::SetRotation();
}

void ActionGame::CDropKickSkillAction::Execution()
{
}

void ActionGame::CDropKickSkillAction::Move(float x)
{
	Velocity()->SetVelocityX(x * parameter_.velocity.x);
}

void ActionGame::CDropKickSkillAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CDropKickSkillAction::GetKey() const
{
	return STATE_KEY_DROPKICK_SKILL;
}
