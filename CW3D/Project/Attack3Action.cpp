#include "Attack3Action.h"

ActionGame::CAttack3Action::CAttack3Action(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CAttack3Action::Start()
{
	CBaseAction::Start();
	
	auto& vel = Velocity();
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	//‚P‰ñ–Ú‚ÌUŒ‚‚Ì‘¬“x‚ðÝ’è
	auto firstVel = parameter_.firstVelocity;
	if (Transform()->IsReverse())
	{
		firstVel *= -1;
	}
	vel->SetVelocity(firstVel);

	CBaseAction::SetRotation();

}

void ActionGame::CAttack3Action::Execution()
{
	//‚Q‰ñ–Ú‚ÌUŒ‚‚Ì‘¬“x‚ðÝ’è
	auto secondVel = parameter_.secondVelocity;
	if (Transform()->IsReverse())
	{
		secondVel *= -1;
	}
	Velocity()->SetVelocity(secondVel);
}

void ActionGame::CAttack3Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::CAttack3Action::GetKey() const
{
	return STATE_KEY_ATTACK3;
}
