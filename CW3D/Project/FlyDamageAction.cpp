#include "FlyDamageAction.h"
#include "ParameterDefine.h"

ActionGame::CFlyDamageAction::CFlyDamageAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CFlyDamageAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
	vel->SetVelocity(knockBack);
	vel->SetGravity(parameter_.gravity);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	//Õ“Ë”»’è‰ñ”ðON
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = true;
}

void ActionGame::CFlyDamageAction::Execution()
{
}

void ActionGame::CFlyDamageAction::End()
{
	//Õ“Ë”»’è‰ñ”ðOFF
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = false;
}

const ActionGame::ActionKeyType ActionGame::CFlyDamageAction::GetKey() const
{
	return STATE_KEY_FLY_DAMAGE;
}
