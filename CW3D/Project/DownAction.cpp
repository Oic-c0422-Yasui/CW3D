#include "DownAction.h"

ActionGame::DownAction::DownAction(Parameter param)
	: CAction()
	, m_Parameter(param)
{
}

void ActionGame::DownAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
}

void ActionGame::DownAction::Execution()
{
}

void ActionGame::DownAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::DownAction::GetKey() const
{
	return STATE_KEY_DOWN;
}
