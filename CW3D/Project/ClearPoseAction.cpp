#include "ClearPoseAction.h"

ActionGame::ClearPoseAction::ClearPoseAction(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::ClearPoseAction::Start()
{
	if (Transform()->GetPositionY() > 0.0f)
	{
		AnimationState()->ChangeMotionByName(m_Parameter.fallAnim.name, m_Parameter.fallAnim.startTime, m_Parameter.fallAnim.speed,
			m_Parameter.fallAnim.tTime, m_Parameter.fallAnim.loopFlg, MOTIONLOCK_OFF, TRUE);
	}
	else
	{
		StartAnim();
	}

	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
	float rotateY = Transform()->GetRotateY();

	Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.18f);
	Velocity()->SetGravity(m_Parameter.gravity);
	Velocity()->SetMaxGravity(m_Parameter.maxGravity);
}

void ActionGame::ClearPoseAction::Execution()
{
}

void ActionGame::ClearPoseAction::End()
{
}

void ActionGame::ClearPoseAction::StartAnim()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
}

const ActionGame::ActionKeyType ActionGame::ClearPoseAction::GetKey() const
{
	return STATE_KEY_CLEARPOSE;
}
