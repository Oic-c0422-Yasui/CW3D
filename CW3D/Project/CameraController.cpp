#include "CameraController.h"
#include "InterpolateCamera.h"
#include "TimeController.h"


CCameraController::CCameraController()
	: Singleton<CCameraController>()
	, m_TimerStartFlg(false)
	, m_LeapFlg(false)
	, m_LeapStartFlg(false)
	, m_LeapEndFlg(false)
	, m_LeapTime(0.0f)
	, m_CurrentTime(0.0f)
	, m_TempLeapEndTime(0.0f)
	, m_Time(0.0f)
	
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
	if (!m_LeapStartFlg)
	{
		m_LeapFlg = false;
		m_LeapEndFlg = false;
	}
	else
	{
		m_LeapStartFlg = false;
	}
}

void CCameraController::SetCamera(const CameraPtr& camera, float tTime, Sample::MyUtilities::EASING_TYPE startEaseType, float leapStartTime, Sample::MyUtilities::EASING_TYPE endEaseType,float leapEndTime)
{
	InterpolateCameraPtr pCamera = std::make_shared<CInterpolateCamera>(m_Camera->GetTargetPos(), m_Camera->GetTargetLookPos(), m_Camera->GetOffsetPos(), m_Camera->GetOffsetLookPos());
	pCamera->Set(leapStartTime,startEaseType, camera);
	m_Camera = pCamera;
	SetCamera(m_Camera);
	m_LeapFlg = true;
	m_TimerStartFlg = false;
	m_NextCamera = camera;
	m_LeapTime = tTime;
	m_LeapStartFlg = true;
	m_LeapEndFlg = false;
	m_TempLeapEndTime = leapEndTime;
	m_EndEaseType = endEaseType;
	pCamera.reset();
}

void CCameraController::SetDefault()
{
	m_LeapStartFlg = false;
	m_LeapFlg = false;
	m_LeapEndFlg = false;
	m_TimerStartFlg = false;
	m_DefaultCamera->SetResetFlg(true);
	SetCamera(m_DefaultCamera);
}

void CCameraController::Update(Vector3 pos, Vector3 lookPos)
{
	if (m_LeapStartFlg)
	{
		if (m_Camera->IsEnd())
		{
			SetCamera(m_NextCamera, m_LeapTime);
		}
	}
	if (m_TimerStartFlg)
	{
		if (m_Time > m_CurrentTime)
		{
			m_CurrentTime += CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
		}
		else
		{
			m_TimerStartFlg = false;
			if (m_LeapFlg)
			{
				m_LeapFlg = false;
				m_LeapEndFlg = true;
				InterpolateCameraPtr pCamera = std::make_shared<CInterpolateCamera>(m_Camera->GetTargetPos(), m_Camera->GetTargetLookPos(), m_Camera->GetOffsetPos(), m_Camera->GetOffsetLookPos());
				m_DefaultCamera->SetPos(pos + m_DefaultCamera->GetOffsetPos());
				m_DefaultCamera->SetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());
				m_DefaultCamera->SetTargetPos(pos + m_DefaultCamera->GetOffsetPos());
				m_DefaultCamera->SetTargetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());

				pCamera->Set(m_TempLeapEndTime, m_EndEaseType, m_DefaultCamera);
				m_Camera = pCamera;
				SetCamera(m_Camera);
				pCamera.reset();
			}
			else
			{
				SetDefault();
			}
		}
	}
	if (m_LeapEndFlg)
	{
		if (m_Camera->IsEnd())
		{
			m_DefaultCamera->SetPos(pos + m_DefaultCamera->GetOffsetPos());
			m_DefaultCamera->SetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());
			m_DefaultCamera->SetTargetPos(pos + m_DefaultCamera->GetOffsetPos());
			m_DefaultCamera->SetTargetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());
			SetDefault();
			m_LeapEndFlg = false;
		}
	}
	m_Camera->Update(pos, lookPos);
}

void CCameraController::Reset()
{
	
}

void CCameraController::Render2DDebug()
{
	//CGraphicsUtilities::RenderString(300, 100, "CameraOff X:%.2f,Y:%.2f,Z:%.2f", m_OffsetPos.x, m_OffsetPos.y, m_OffsetPos.z);
}

