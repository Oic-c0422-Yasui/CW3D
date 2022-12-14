#include "StartPoseState.h"
#include "FixedCamera.h"
#include "CameraController.h"
#include "TimeScaleController.h"

ActionGame::StartPoseState::StartPoseState(Parameter param)
	: State()
	, m_CurrentTime(0)
	, m_Parameter(param)
{
}

void ActionGame::StartPoseState::Start()
{
	m_CurrentTime = 0.0f;
	m_Action = Actor()->GetAction<StartPoseAction>(GetKey());
	m_Action->Start();
	//�J�����ݒ�
	MyUtilities::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(-5,2,-3)},
			{m_Parameter.Time,Vector3(5,2,-3)},
			{m_Parameter.Time,Vector3(0,2,-3)},
		}
	);
	MyUtilities::ANIM_V3_DATA_ARRAY animLookPos(
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
	camera->SetAnim(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera);
	m_Action->StartAnim();
}

void ActionGame::StartPoseState::Execution()
{
	if (m_Parameter.Time > m_CurrentTime)
	{
		m_Action->Execution();
		m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
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
	//�J�������f�t�H���g�ɖ߂�
	CameraControllerInstance.SetDefault();
}

void ActionGame::StartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::StartPoseState::GetKey() const
{
	return STATE_KEY_STARTPOSE;
}