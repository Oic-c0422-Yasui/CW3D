#include "DamageAction.h"

ActionGame::DamageAction::DamageAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::DamageAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);

	Velocity()->SetMaxGravity(m_Parameter.maxGravity);
	Velocity()->SetGravity(m_Parameter.gravity);
	Velocity()->SetVelocity(knockBack);

	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
}

void ActionGame::DamageAction::Execution()
{
}

void ActionGame::DamageAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::DamageAction::GetKey() const
{
	return STATE_KEY_DAMAGE;
}
