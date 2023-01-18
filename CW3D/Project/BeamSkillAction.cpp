#include "BeamSkillAction.h"

ActionGame::BeamSkillAction::BeamSkillAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::BeamSkillAction::Start()
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

void ActionGame::BeamSkillAction::Execution()
{
}

void ActionGame::BeamSkillAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::BeamSkillAction::GetKey() const
{
	return STATE_KEY_BEAM_SKILL;
}
