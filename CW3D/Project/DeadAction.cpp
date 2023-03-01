#include "DeadAction.h"
#include "ParameterDefine.h"

ActionGame::CDeadAction::CDeadAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
	, currentTime_(0.0f)
{
}

void ActionGame::CDeadAction::Start()
{
	CBaseAction::Start();

	Velocity()->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	currentTime_ = 0.0f;
}

void ActionGame::CDeadAction::Execution()
{
	if (AnimationState()->IsEndMotion())
	{
		currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
		auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		alpha = MyUtil::Timer(1.0f, currentTime_, 0, parameter_.finishTime);
	}
}

void ActionGame::CDeadAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CDeadAction::GetKey() const
{
	return STATE_KEY_DEAD;
}
