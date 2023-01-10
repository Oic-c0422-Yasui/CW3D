#include "NPCStartPoseAction.h"

ActionGame::NPCStartPoseAction::NPCStartPoseAction(Parameter param)
	: Action()
	, m_Parameter(param)
{
}

void ActionGame::NPCStartPoseAction::Start()
{
	StartAnim();
	

	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
	float rotateY = Transform()->GetRotateY();

	Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.18f);
	Velocity()->SetGravity(m_Parameter.gravity);
	Velocity()->SetMaxGravity(m_Parameter.maxGravity);
	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.0f);
		
		Transform()->Add
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.0f);
	}
}

void ActionGame::NPCStartPoseAction::Execution()
{

}

void ActionGame::NPCStartPoseAction::End()
{
}

void ActionGame::NPCStartPoseAction::StartAnim()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
}

const ActionGame::ActionKeyType ActionGame::NPCStartPoseAction::GetKey() const
{
	return STATE_KEY_NPCSTARTPOSE;
}
