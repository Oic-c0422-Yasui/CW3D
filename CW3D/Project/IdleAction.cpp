#include "IdleAction.h"

ActionGame::IdleAction::IdleAction(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::IdleAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.15f);
	}
}

void ActionGame::IdleAction::Execution()
{
}

void ActionGame::IdleAction::End()
{
}

void ActionGame::IdleAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

void ActionGame::IdleAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::IdleAction::GetKey() const
{
	return STATE_KEY_IDLE;
}
