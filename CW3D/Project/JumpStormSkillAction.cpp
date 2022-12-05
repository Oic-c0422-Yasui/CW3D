#include "JumpStormSkillAction.h"

ActionGame::JumpStormSkillAction::JumpStormSkillAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::JumpStormSkillAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

	Velocity()->SetGravityFlg(false);
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

void ActionGame::JumpStormSkillAction::Execution()
{
}

void ActionGame::JumpStormSkillAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

void ActionGame::JumpStormSkillAction::End()
{
	Velocity()->SetGravityFlg(true);
}

const ActionGame::ActionKeyType ActionGame::JumpStormSkillAction::GetKey() const
{
	return STATE_KEY_JUMPSTORMSKILL;
}
