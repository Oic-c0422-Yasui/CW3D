#include "ShockWaveSkillAction.h"

ActionGame::ShockWaveSkillAction::ShockWaveSkillAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::ShockWaveSkillAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	Velocity()->SetGravityFlg(false);
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

void ActionGame::ShockWaveSkillAction::Execution()
{
}

void ActionGame::ShockWaveSkillAction::End()
{
	Velocity()->SetGravityFlg(true);
}

const ActionGame::ActionKeyType ActionGame::ShockWaveSkillAction::GetKey() const
{
	return STATE_KEY_SHOCKWAVE_SKILL;
}
