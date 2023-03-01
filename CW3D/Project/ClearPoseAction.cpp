#include "ClearPoseAction.h"

ActionGame::ClearPoseAction::ClearPoseAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::ClearPoseAction::Start()
{
	if (Transform()->GetPositionY() > 0.0f)
	{
		auto anim = parameter_.fallAnim;
		CBaseAction::PlayAnimation(anim.name, anim.startTime, anim.speed, anim.tTime, anim.isLoop);
	}
	else
	{
		CBaseAction::PlayAnimation();
	}

	auto& vel = Velocity();
	float rotateY = Transform()->GetRotateY();
	vel->SetRotateY(rotateY, MOF_ToRadian(0), 0.18f);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	vel->SetGravity(parameter_.gravity);
	vel->SetMaxGravity(parameter_.maxGravity);
}

void ActionGame::ClearPoseAction::Execution()
{
}

void ActionGame::ClearPoseAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::ClearPoseAction::GetKey() const
{
	return STATE_KEY_CLEARPOSE;
}
