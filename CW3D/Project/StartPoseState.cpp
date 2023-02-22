#include "StartPoseState.h"
#include "FixedCamera.h"
#include "CameraController.h"
#include "TimeScaleController.h"

ActionGame::StartPoseState::StartPoseState(Parameter param)
	: State()
	, currentTime_(0)
	, m_Parameter(param)
{
}

void ActionGame::StartPoseState::Start()
{
	currentTime_ = 0.0f;
	m_Action = Actor()->GetAction<StartPoseAction>(GetKey());
	m_Action->Start();
	//カメラ設定
	MyUtil::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(-5,2,-3)},
			{m_Parameter.Time,Vector3(5,2,-3)},
			{m_Parameter.Time,Vector3(0,2,-3)},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY animLookPos(
		{
			{0.0f,Vector3(0, 1, 0)},
			{0.0f,Vector3(0, 1, 0)},
			{m_Parameter.Time,Vector3(0, 1, 0)},
		}
	);
	Vector3 offsetPos(7, 2, -2);
	Vector3 offsetLookPos(0, 0, 0);
	CameraPtr camera;
	camera = std::make_shared<FixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), offsetPos, offsetLookPos);
	camera->SetAnimation(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera);
	TimeScaleControllerInstance.SetTimeScale(CHARA_TYPE::ENEMY, 0.0f, 0.0f);
}

void ActionGame::StartPoseState::Execution()
{
	if (m_Parameter.Time > currentTime_)
	{
		m_Action->Execution();
		currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::StartPoseState::InputExecution()
{

}

void ActionGame::StartPoseState::End()
{
	m_Action->End();
	//カメラをデフォルトに戻す
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.SetTimeScale(CHARA_TYPE::ENEMY, 1.0f, 0.0f);
}

void ActionGame::StartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::StartPoseState::GetKey() const
{
	return STATE_KEY_STARTPOSE;
}
