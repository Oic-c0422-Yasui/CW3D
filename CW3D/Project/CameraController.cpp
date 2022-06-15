#include "CameraController.h"
#include "InterpolateCamera.h"



CCameraController::CCameraController()
	: Singleton<CCameraController>()
	
{
}

CCameraController::~CCameraController()
{
}

void CCameraController::Load(const CameraPtr& camera)
{
	m_DefaultCamera = camera;
	SetDefault();
}

void CCameraController::SetCamera(const CameraPtr& camera)
{
	m_Camera = camera;
	m_Camera->Create();
	CGraphicsUtilities::SetCamera(&m_Camera->GetCamera());
}

void CCameraController::SetCamera(const CameraPtr& camera, float tTime)
{
	SetCamera(camera);
	m_Time = tTime;
	m_CurrentTime = 0.0f;
	m_TimerStartFlg = true;

}

void CCameraController::SetCamera(const CameraPtr& camera, float tTime, Sample::MyUtilities::EASING_TYPE startEaseType, float leapStartTime, Sample::MyUtilities::EASING_TYPE endEaseType,float leapEndTime)
{
	InterpolateCameraPtr pCamera = std::shared_ptr<CInterpolateCamera>();
	pCamera->Set(leapStartTime,startEaseType,m_NextCamera);
	m_Camera = pCamera;
	SetCamera(m_Camera);

	m_NextCamera = camera;
	m_LeapFlg = true;
	m_EndLeapTime = leapEndTime;
	m_EndLeapFlg = false;
	m_EndEaseType = endEaseType;
}

void CCameraController::Update(Vector3 pos, Vector3 lookPos)
{
	if (m_TimerStartFlg)
	{
		if (m_Time > m_CurrentTime)
		{
			m_CurrentTime += CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
		}
	}
	m_Camera->Update(pos, lookPos);
}

void CCameraController::Render2DDebug()
{
	//CGraphicsUtilities::RenderString(300, 100, "CameraOff X:%.2f,Y:%.2f,Z:%.2f", m_OffsetPos.x, m_OffsetPos.y, m_OffsetPos.z);
}

