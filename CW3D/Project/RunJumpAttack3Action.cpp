#include "RunJumpAttack3Action.h"

ActionGame::RunJumpAttack3Action::RunJumpAttack3Action(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::RunJumpAttack3Action::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

	auto& vel = Velocity();
	vel->SetVelocityY(m_Parameter.jumpPower);
	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
		vel->SetVelocityX(-m_Parameter.velocity.x);
	}
	else
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
		vel->SetVelocityX(m_Parameter.velocity.x);
	}
}

void ActionGame::RunJumpAttack3Action::Execution()
{
	if (Transform()->IsReverse())
	{
		Velocity()->SetVelocity(Vector3(-0.1f, 0, 0));
	}
	else
	{
		Velocity()->SetVelocity(Vector3(0.1f, 0, 0));
	}
}

void ActionGame::RunJumpAttack3Action::End()
{
	Velocity()->SetGravity(m_Parameter.defaultGravity);
}

void ActionGame::RunJumpAttack3Action::Jump()
{
	Velocity()->SetVelocityY(m_Parameter.jumpPower);
}

const ActionGame::ActionKeyType ActionGame::RunJumpAttack3Action::GetKey() const
{
	return STATE_KEY_RUNJUMPATTACK3;
}