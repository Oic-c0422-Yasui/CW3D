#include "DropKickSkillAction.h"

ActionGame::DropKickSkillAction::DropKickSkillAction(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::DropKickSkillAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& vel = Velocity();

	vel->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

	vel->SetMaxGravity(m_Parameter.maxGravity);
	vel->SetVelocityY(m_Parameter.jumpPower);
	vel->SetGravity(m_Parameter.gravity);
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

void ActionGame::DropKickSkillAction::Execution()
{
}

void ActionGame::DropKickSkillAction::Move(float x)
{
	Velocity()->SetVelocityX(x * m_Parameter.velocity.x);
}

void ActionGame::DropKickSkillAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::DropKickSkillAction::GetKey() const
{
	return STATE_KEY_DROPKICK_SKILL;
}
