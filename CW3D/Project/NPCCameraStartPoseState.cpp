#include "NPCCameraStartPoseState.h"
#include "FixedCamera.h"
#include "CameraController.h"
#include "TimeScaleController.h"



ActionGame::NPCCameraStartPoseState::NPCCameraStartPoseState(Parameter param)
	: State()
	, m_CurrentTime(0)
	, m_Parameter(param)
	, m_StartFlg(false)
{
}

void ActionGame::NPCCameraStartPoseState::Start()
{
	m_CurrentTime = 0.0f;
	m_Action = Actor()->GetAction<NPCStartPoseAction>(GetKey());
	m_Action->Start();
	m_StartFlg = false;
}

void ActionGame::NPCCameraStartPoseState::Execution()
{

	if (!m_StartFlg)
	{
		SettingCamera();
		m_StartFlg = true;
	}
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

void ActionGame::NPCCameraStartPoseState::InputExecution()
{
}

void ActionGame::NPCCameraStartPoseState::End()
{
	m_Action->End();
	//カメラをデフォルトに戻す
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.SetTimeScale(CHARA_TYPE::PLAYER, 1.0f, 0.0f);
}

void ActionGame::NPCCameraStartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::NPCCameraStartPoseState::GetKey() const
{
	return STATE_KEY_NPC_STARTPOSE;
}

void ActionGame::NPCCameraStartPoseState::SettingCamera()
{
	//カメラ設定
	MyUtilities::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(5,2,-3)},
			{m_Parameter.Time * 0.5f,Vector3(-7,2,-3)},
			{m_Parameter.Time * 0.5f,Vector3(-7,2,-3)},
		}
	);
	MyUtilities::ANIM_V3_DATA_ARRAY animLookPos(
		{
			{0.0f,Vector3(0, 2, 0)},
			{0.0f,Vector3(0, 2, 0)},
			{m_Parameter.Time,Vector3(0, 2, 0)},
		}
	);
	Vector3 offsetPos(5, 2, -2);
	Vector3 offsetLookPos(0, 2, 0);
	CameraPtr camera;
	camera = std::make_shared<FixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), offsetPos, offsetLookPos);
	camera->SetAnim(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera);
	TimeScaleControllerInstance.SetTimeScale(CHARA_TYPE::PLAYER, 0.0f, 0.0f);
}