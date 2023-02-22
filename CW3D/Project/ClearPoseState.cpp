#include "ClearPoseState.h"
#include "CameraController.h"
#include "FixedCamera.h"

ActionGame::ClearPoseState::ClearPoseState()
	: State()
	, currentTime_(0)
	, m_AnimStartFlg(false)
{
}

void ActionGame::ClearPoseState::Start()
{
	currentTime_ = 0.0f;
	m_ClearPoseAction = Actor()->GetAction<ClearPoseAction>(GetKey());
	m_ClearPoseAction->Start();
	m_AnimStartFlg = false;
}

void ActionGame::ClearPoseState::Execution()
{
	m_ClearPoseAction->Execution();
	if (Actor()->GetTransform()->GetPositionY() > 0.0f || m_AnimStartFlg)
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
	camera = std::make_shared<FixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), offsetPos, offsetLookPos);
	camera->SetAnimation(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera);


	m_ClearPoseAction->StartAnim();
	m_AnimStartFlg = true;
}

void ActionGame::ClearPoseState::End()
{
	m_ClearPoseAction->End();
}

void ActionGame::ClearPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::ClearPoseState::GetKey() const
{
	return STATE_KEY_CLEARPOSE;
}
