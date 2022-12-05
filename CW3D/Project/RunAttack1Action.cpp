#include "RunAttack1Action.h"

ActionGame::RunAttack1Action::RunAttack1Action(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::RunAttack1Action::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);


	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
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

void ActionGame::RunAttack1Action::Execution()
{
}

void ActionGame::RunAttack1Action::End()
{
}

const ActionGame::ActionKeyType ActionGame::RunAttack1Action::GetKey() const
{
	return STATE_KEY_RUNATTACK1;
}
