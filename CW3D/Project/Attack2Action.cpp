#include "Attack2Action.h"

ActionGame::Attack2Action::Attack2Action(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::Attack2Action::Start()
{

	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
		//x:0.1f
		Velocity()->SetVelocity(Vector3(-m_Parameter.velocity.x, m_Parameter.velocity.y, m_Parameter.velocity.z));
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
		//x:0.1f
		Velocity()->SetVelocity(Vector3(m_Parameter.velocity.x, m_Parameter.velocity.y, m_Parameter.velocity.z));
	}
	//PLAYERSPEED * 0.3
	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
}

void ActionGame::Attack2Action::Execution()
{
}

void ActionGame::Attack2Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::Attack2Action::GetKey() const
{
	return STATE_KEY_ATTACK2;
}
