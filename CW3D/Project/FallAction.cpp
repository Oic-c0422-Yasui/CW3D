#include "FallAction.h"

ActionGame::FallAction::FallAction(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::FallAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& vel = Velocity();

	vel->SetMaxVelocity(m_Parameter.maxVelocty.x, m_Parameter.maxVelocty.z);


	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

	vel->SetMaxGravity(m_Parameter.maxGravity);

	vel->SetGravity(m_Parameter.gravity);

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

void ActionGame::FallAction::Execution()
{
}

void ActionGame::FallAction::End()
{
}

void ActionGame::FallAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

void ActionGame::FallAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::FallAction::GetKey() const
{
	return STATE_KEY_FALL;
}
