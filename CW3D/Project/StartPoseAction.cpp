#include "StartPoseAction.h"

ActionGame::CStartPoseAction::CStartPoseAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, parameter_(param)
{
}

void ActionGame::CStartPoseAction::Start()
{
	CBaseAction::Start();

	float rotateY = Transform()->GetRotateY();
	auto& vel = Velocity();
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);
	vel->SetRotateY(rotateY, MOF_ToRadian(0), 0.18f);
	vel->SetGravity(parameter_.gravity);
	vel->SetMaxGravity(parameter_.maxGravity);
	
	CBaseAction::SetRotation();
}

void ActionGame::CStartPoseAction::Execution()
{
}

void ActionGame::CStartPoseAction::End()
{
}

const ActionGame::ActionKeyType ActionGame::CStartPoseAction::GetKey() const
{
	return STATE_KEY_STARTPOSE;
}
