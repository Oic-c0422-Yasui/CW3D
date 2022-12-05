#include "Attack1Action.h"

ActionGame::Attack1Action::Attack1Action(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::Attack1Action::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
		Velocity()->SetVelocityX(-m_Parameter.velocity.x);
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
		Velocity()->SetVelocityX(m_Parameter.velocity.x);
	}
}

void ActionGame::Attack1Action::Execution()
{
}

void ActionGame::Attack1Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::Attack1Action::GetKey() const
{
	return STATE_KEY_ATTACK1;
}
