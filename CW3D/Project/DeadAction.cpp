#include "DeadAction.h"
#include "ParameterDefine.h"

ActionGame::DeadAction::DeadAction(Parameter param)
	: CAction()
	, m_Parameter(param)
	, currentTime_(0.0f)
{
}

void ActionGame::DeadAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
	Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
	currentTime_ = 0;
}

void ActionGame::DeadAction::Execution()
{
	if (AnimationState()->IsEndMotion())
	{
		currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
		auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		alpha = MyUtil::Timer(1.0f, currentTime_, 0, m_Parameter.finishTime);
	}
}

void ActionGame::DeadAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::DeadAction::GetKey() const
{
	return STATE_KEY_DEAD;
}
