#include "IdleMotionAction.h"

ActionGame::IdleMotionAction::IdleMotionAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::IdleMotionAction::Start()
{

	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(180), 0.2f);
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.2f);
	}
}

void ActionGame::IdleMotionAction::Execution()
{
}

void ActionGame::IdleMotionAction::End()
{
}

void ActionGame::IdleMotionAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

const ActionGame::ActionKeyType ActionGame::IdleMotionAction::GetKey() const
{
	return STATE_KEY_IDLEMOTION;
}
