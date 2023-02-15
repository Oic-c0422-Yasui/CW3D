#include "JumpBeamSkillAction.h"

ActionGame::JumpBeamSkillAction::JumpBeamSkillAction(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::JumpBeamSkillAction::Start()
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

void ActionGame::JumpBeamSkillAction::Execution()
{
}

void ActionGame::JumpBeamSkillAction::End()
{
	Velocity()->SetGravityFlg(true);
}

const ActionGame::ActionKeyType ActionGame::JumpBeamSkillAction::GetKey() const
{
	return STATE_KEY_JUMP_BEAM_SKILL;
}
