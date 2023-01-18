#include "RunJumpAttack2Action.h"

ActionGame::RunJumpAttack2Action::RunJumpAttack2Action(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::RunJumpAttack2Action::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& vel = Velocity();

	vel->SetVelocityY(m_Parameter.jumpPower);
	vel->SetGravity(m_Parameter.gravity);

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

void ActionGame::RunJumpAttack2Action::Execution()
{
}

void ActionGame::RunJumpAttack2Action::End()
{
	Velocity()->SetGravity(m_Parameter.defaultGravity);
}

const ActionGame::ActionKeyType ActionGame::RunJumpAttack2Action::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK2;
}
