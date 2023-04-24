#include "StartPoseState.h"
#include "FixedCamera.h"
#include "CameraController.h"
#include "TimeScaleController.h"

ActionGame::CStartPoseState::CStartPoseState(Parameter param)
	: CBaseState()
	, currentTime_(0)
	, parameter_(param)
{
}

void ActionGame::CStartPoseState::Start()
{
	currentTime_ = 0.0f;
	action_ = Actor()->GetAction<CStartPoseAction>(GetKey());
	action_->Start();
	//カメラ設定
	MyUtil::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(-5,2,-3)},
			{parameter_.Time,Vector3(5,2,-3)},
			{parameter_.Time,Vector3(0,2,-3)},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY animLookPos(
		{
			{0.0f,Vector3(0, 1, 0)},
			{0.0f,Vector3(0, 1, 0)},
			{parameter_.Time,Vector3(0, 1, 0)},
		}
	);
	Vector3 offsetPos(7, 2, -2);
	Vector3 offsetLookPos(0, 0, 0);
	CameraPtr camera;
	camera = std::make_shared<CFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), offsetPos, offsetLookPos);
	camera->SetAnimation(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera);
	TimeScaleControllerInstance.SetOtherTimeScale(Actor()->GetType() , 0.0f, 0.0f);
}

void ActionGame::CStartPoseState::Execution()
{
	if (parameter_.Time > currentTime_)
	{
		action_->Execution();
		currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CStartPoseState::InputExecution()
{

}

void ActionGame::CStartPoseState::End()
{
	action_->End();
	//カメラをデフォルトに戻す
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.SetOtherTimeScale(Actor()->GetType(), 1.0f, 0.0f);
}

void ActionGame::CStartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CStartPoseState::GetKey() const
{
	return STATE_KEY_STARTPOSE;
}
