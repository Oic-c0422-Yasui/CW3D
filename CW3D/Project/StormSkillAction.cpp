#include "StormSkillAction.h"

ActionGame::StormSkillAction::StormSkillAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::StormSkillAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& vel = Velocity();

	vel->SetMaxVelocity(m_Parameter.maxVelocity.x, m_Parameter.maxVelocity.z);
	vel->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

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

void ActionGame::StormSkillAction::Execution()
{
}

void ActionGame::StormSkillAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

void ActionGame::StormSkillAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::StormSkillAction::GetKey() const
{
	return STATE_KEY_STORM_SKILL;
}
