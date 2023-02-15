#include "Attack3Action.h"

ActionGame::Attack3Action::Attack3Action(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::Attack3Action::Start()
{

	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);

		Velocity()->SetVelocity(Vector3(-m_Parameter.velocity.x, m_Parameter.velocity.y, m_Parameter.velocity.z));
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);

		Velocity()->SetVelocity(Vector3(m_Parameter.velocity.x, m_Parameter.velocity.y, m_Parameter.velocity.z));
	}

	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
}

void ActionGame::Attack3Action::Execution()
{
	if (Transform()->IsReverse())
	{
		//x:0.1f
		Velocity()->SetVelocity(Vector3(-m_Parameter.velocity2.x, m_Parameter.velocity2.y, m_Parameter.velocity2.z));
	}
	else
	{
		Velocity()->SetVelocity(Vector3(m_Parameter.velocity2.x, m_Parameter.velocity2.y, m_Parameter.velocity2.z));
	}
}

void ActionGame::Attack3Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::Attack3Action::GetKey() const
{
	return STATE_KEY_ATTACK3;
}
