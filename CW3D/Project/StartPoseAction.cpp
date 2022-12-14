#include "StartPoseAction.h"

ActionGame::StartPoseAction::StartPoseAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::StartPoseAction::Start()
{
	StartAnim();


	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
	float rotateY = Transform()->GetRotateY();

	Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.18f);
	Velocity()->SetGravity(m_Parameter.gravity);
	Velocity()->SetMaxGravity(m_Parameter.maxGravity);
}

void ActionGame::StartPoseAction::Execution()
{
}

void ActionGame::StartPoseAction::End()
{
}

void ActionGame::StartPoseAction::StartAnim()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
}

const ActionGame::ActionKeyType ActionGame::StartPoseAction::GetKey() const
{
	return STATE_KEY_STARTPOSE;
}
