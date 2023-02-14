#include "FlyDamageAction.h"
#include "ParameterDefine.h"

ActionGame::FlyDamageAction::FlyDamageAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::FlyDamageAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);

	Velocity()->SetMaxGravity(m_Parameter.maxGravity);

	Velocity()->SetGravity(m_Parameter.gravity);
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = true;
	Velocity()->SetVelocity(knockBack);

	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
}

void ActionGame::FlyDamageAction::Execution()
{
}

void ActionGame::FlyDamageAction::End()
{
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = false;
}

const ActionGame::ActionKeyType ActionGame::FlyDamageAction::GetKey() const
{
	return STATE_KEY_FLY_DAMAGE;
}
