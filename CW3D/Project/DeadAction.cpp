#include "DeadAction.h"

ActionGame::DeadAction::DeadAction(Parameter param)
	: Action()
	, m_Parameter(param)
	, m_CurrentTime(0.0f)
{
}

void ActionGame::DeadAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
	m_CurrentTime = 0;
}

void ActionGame::DeadAction::Execution()
{
	if (AnimationState()->IsEndMotion())
	{
		m_CurrentTime += CUtilities::GetFrameSecond();
		auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		alpha = MyUtilities::Timer(1.0f, m_CurrentTime, 0, m_Parameter.finishTime);
	}
}

void ActionGame::DeadAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::DeadAction::GetKey() const
{
	return STATE_KEY_DEAD;
}
