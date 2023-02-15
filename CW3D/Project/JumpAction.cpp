#include "JumpAction.h"

ActionGame::JumpAction::JumpAction(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::JumpAction::Start()
{

	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& vel = Velocity();


	vel->SetMaxVelocity(m_Parameter.maxVelocity.x, m_Parameter.maxVelocity.z);

	vel->SetMaxGravity(m_Parameter.maxGravity);

	vel->SetVelocityY(m_Parameter.jumpPower);

	vel->SetGravity(m_Parameter.gravity);

	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
	}
	else
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
	}
}

void ActionGame::JumpAction::Execution()
{
}

void ActionGame::JumpAction::End()
{
}

void ActionGame::JumpAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

void ActionGame::JumpAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::JumpAction::GetKey() const
{
	return STATE_KEY_JUMP;
}
