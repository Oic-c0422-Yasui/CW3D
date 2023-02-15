#include "JumpAttack1Action.h"

ActionGame::JumpAttack1Action::JumpAttack1Action(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::JumpAttack1Action::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
	Velocity()->SetGravity(m_Parameter.gravity);
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

void ActionGame::JumpAttack1Action::Execution()
{
}

void ActionGame::JumpAttack1Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::JumpAttack1Action::GetKey() const
{
	return STATE_KEY_JUMP_ATTACK1;
}
