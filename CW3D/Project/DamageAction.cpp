#include "DamageAction.h"
#include "ParameterDefine.h"

ActionGame::CDamageAction::CDamageAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CDamageAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
	vel->SetVelocity(knockBack);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetGravity(parameter_.gravity);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
}

void ActionGame::CDamageAction::Execution()
{
}

void ActionGame::CDamageAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CDamageAction::GetKey() const
{
	return STATE_KEY_DAMAGE;
}
