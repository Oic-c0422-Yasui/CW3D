#include "RunLandingAction.h"

ActionGame::RunLandingAction::RunLandingAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::RunLandingAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

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

void ActionGame::RunLandingAction::Execution()
{
}

void ActionGame::RunLandingAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::RunLandingAction::GetKey() const
{
	return STATE_KEY_RUN_LANDING;
}
