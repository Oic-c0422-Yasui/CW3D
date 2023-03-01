#include "NPCCameraStartPoseState.h"
#include "FixedCamera.h"
#include "CameraController.h"
#include "TimeScaleController.h"



ActionGame::CNPCFollowCameraStartPoseState::CNPCFollowCameraStartPoseState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStart_(false)
	, isEffectStart_(false)
{
}

void ActionGame::CNPCFollowCameraStartPoseState::Start()
{
	CAttackBaseState::Start();
	action_ = Actor()->GetAction<CNPCStartPoseAction>(GetKey());
	action_->Start();
	isStart_ = false;
	isEffectStart_ = false;
}

void ActionGame::CNPCFollowCameraStartPoseState::Execution()
{
	if (!isStart_)
	{
		SettingCamera();
		isStart_ = true;
	}
	if (parameter_.EffectStartTime < currentTime_ && !isEffectStart_)
	{
		CreateEffect();
		isEffectStart_ = true;
	}
	if (parameter_.Time > currentTime_)
	{
		action_->Execution();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CNPCFollowCameraStartPoseState::InputExecution()
{
}

void ActionGame::CNPCFollowCameraStartPoseState::End()
{
	CAttackBaseState::End();
	action_->End();
	//カメラをデフォルトに戻す
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.SetOtherTimeScale(Actor()->GetType(), 1.0f, 0.0f);
}

void ActionGame::CNPCFollowCameraStartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CNPCFollowCameraStartPoseState::GetKey() const
{
	return STATE_KEY_NPC_STARTPOSE;
}

void ActionGame::CNPCFollowCameraStartPoseState::SettingCamera()
{
	//カメラ設定
	MyUtil::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(5,2,-3)},
			{parameter_.Time * 0.5f,Vector3(-7,2,-3)},
			{parameter_.Time * 0.5f,Vector3(-7,2,-3)},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY animLookPos(
		{
			{0.0f,Vector3(0, 2, 0)},
			{0.0f,Vector3(0, 2, 0)},
			{parameter_.Time,Vector3(0, 2, 0)},
		}
	);
	Vector3 offsetPos(5, 2, -2);
	Vector3 offsetLookPos(0, 2, 0);
	CameraPtr camera;
	camera = std::make_shared<CFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), offsetPos, offsetLookPos);
	camera->SetAnimation(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera);
	TimeScaleControllerInstance.SetOtherTimeScale(Actor()->GetType(), 0.0f, 0.0f);
}