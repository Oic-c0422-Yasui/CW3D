#include "NPCStartPoseAction.h"
#include "ParameterDefine.h"

ActionGame::CNPCStartPoseAction::CNPCStartPoseAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
	, tmpOffsetPos_(0,0,0)
	, currentTime_(0.0f)
{
}

void ActionGame::CNPCStartPoseAction::Start()
{
	CBaseAction::Start();
	
	if (Transform()->IsReverse())
	{
		tmpOffsetPos_ = parameter_.offsetPos;
	}
	else
	{
		tmpOffsetPos_ = -parameter_.offsetPos;
	}

	tmpOffsetPos_ = Vector3(0, 0, 0);
	currentTime_ = 0.0f;
	Transform()->AddPosition(tmpOffsetPos_);
	
	auto& invincible = ParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	invincible = parameter_.finishTime;

	auto& showHP = ParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
	showHP = false;

	CBaseAction::SetRotation();
}

void ActionGame::CNPCStartPoseAction::Execution()
{

	auto& invincible = ParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = MyUtil::Timer(0.0f, currentTime_, 1.0f, parameter_.finishTime);
}

void ActionGame::CNPCStartPoseAction::End()
{
	Transform()->AddPosition(-tmpOffsetPos_);
	auto& invincible = ParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	auto& showHP = ParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
	showHP = true;
	invincible = 0.0f;
}

const ActionGame::ActionKeyType ActionGame::CNPCStartPoseAction::GetKey() const
{
	return STATE_KEY_NPC_STARTPOSE;
}

bool ActionGame::CNPCStartPoseAction::IsEndAnimation() const noexcept
{
	return currentTime_ >= parameter_.finishTime;
}
