#include "EscapeAction.h"
#include "ParameterDefine.h"

ActionGame::EscapeAction::EscapeAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::EscapeAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
	}
}

void ActionGame::EscapeAction::Execution()
{
}

void ActionGame::EscapeAction::End()
{
	EndThrough();
}

void ActionGame::EscapeAction::Move(float x, float z)
{
	Velocity()->SetVelocityX(x * m_Parameter.velocity.x);
	Velocity()->SetVelocityZ(z * m_Parameter.velocity.z);
}

void ActionGame::EscapeAction::StartThrough()
{
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = true;
}

void ActionGame::EscapeAction::EndThrough()
{
	auto& isThroughCollision = ParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = false;
}

const ActionGame::ActionKeyType ActionGame::EscapeAction::GetKey() const
{
	return STATE_KEY_ESCAPE;
}
