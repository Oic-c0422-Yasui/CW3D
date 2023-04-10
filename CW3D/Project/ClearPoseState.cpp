#include "ClearPoseState.h"
#include "CameraController.h"
#include "FixedCamera.h"
#include "SendMessageServiceDefine.h"

ActionGame::CClearPoseState::CClearPoseState()
	: CState()
	, currentTime_(0)
	, isAnimStart_(false)
{
}

void ActionGame::CClearPoseState::Start()
{
	currentTime_ = 0.0f;
	action_ = Actor()->GetAction<ClearPoseAction>(GetKey());
	action_->Start();
	isAnimStart_ = false;
	SendMessageService::GetService()->Send(GameMessageType::UI_Disable);
}

void ActionGame::CClearPoseState::Execution()
{
	action_->Execution();
	if (Actor()->GetTransform()->GetPositionY() > 0.0f || isAnimStart_)
	{
		return;
	}


	//ÉJÉÅÉâê›íË
	MyUtil::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(-5,2,-3)},
			{5.0f,Vector3(5,2,-3)},
			{5.0f,Vector3(0,2,-3)},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY animLookPos(
		{
			{0.0f,Vector3(0, 1, 0)},
			{0.0f,Vector3(0, 1, 0)},
			{5.0f,Vector3(0, 1, 0)},
		}
	);
	Vector3 offsetPos(7, 2, -2);
	Vector3 offsetLookPos(0, 0, 0);
	CameraPtr camera;
	camera = std::make_shared<CFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), offsetPos, offsetLookPos);
	camera->SetAnimation(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera);


	action_->PlayAnimation();
	isAnimStart_ = true;
}

void ActionGame::CClearPoseState::End()
{
	action_->End();
	SendMessageService::GetService()->Send(GameMessageType::UI_Visible);
}

void ActionGame::CClearPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CClearPoseState::GetKey() const
{
	return STATE_KEY_CLEARPOSE;
}
