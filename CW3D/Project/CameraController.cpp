#include "CameraController.h"
#include "InterpolateCamera.h"
#include "TimeScaleController.h"


using namespace ActionGame;

CameraController::CameraController()
	: Singleton<CameraController>()
	, m_TimerStartFlg(false)
	, m_LeapFlg(false)
	, m_LeapStartFlg(false)
	, m_LeapEndFlg(false)
	, m_LeapTime(0.0f)
	, m_CurrentTime(0.0f)
	, m_TempLeapEndTime(0.0f)
	, m_Time(0.0f)
	, m_QuakePower(0.0f)
	, m_QuakeFrequent(0.0f)
	, m_QuakeTime(0.0f)
	, m_QuakeCurrentTime(0.0f)
	, m_TargetPos(0,0,0)
	, m_TargetLookPos(0,0,0)
	
{
}



CameraController::~CameraController()
{
}

void CameraController::Load(const CameraPtr& camera)
{
	m_DefaultCamera = camera;
	SetDefault();
}

void CameraController::SetCamera(const CameraPtr& camera)
{
	m_Camera = camera;
	m_Camera->Create();
	CGraphicsUtilities::SetCamera(&m_Camera->GetCamera());
}

void CameraController::SetCamera(const CameraPtr& camera, float tTime)
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

void CameraController::SetCamera(const CameraPtr& camera, float tTime, MyUtilities::EASING_TYPE startEaseType, float leapStartTime, MyUtilities::EASING_TYPE endEaseType,float leapEndTime)
{
	InterpolateCameraPtr pCamera = std::make_shared<InterpolateCamera>(m_Camera->GetTargetPos(), m_Camera->GetTargetLookPos(), m_Camera->GetOffsetPos(), m_Camera->GetOffsetLookPos());
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

void CameraController::SetDefault()
{
	m_LeapStartFlg = false;
	m_LeapFlg = false;
	m_LeapEndFlg = false;
	m_TimerStartFlg = false;
	m_DefaultCamera->SetResetFlg(true);
	SetCamera(m_DefaultCamera);
}

void CameraController::Update(const Vector3& pos, const Vector3& lookPos)
{
	if (m_LeapStartFlg)
	{
		if (m_Camera->IsEnd())
		{
			SetCamera(m_NextCamera, m_LeapTime);
		}
	}
	//タイマー
	if (m_TimerStartFlg)
	{
		if (m_Time > m_CurrentTime)
		{
			m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
		}
		else
		{
			//タイマー終了時
			
			m_TimerStartFlg = false;
			//補間フラグがTrueなら
			if (m_LeapFlg)
			{
				m_LeapFlg = false;
				m_LeapEndFlg = true;
				InterpolateCameraPtr pCamera = std::make_shared<InterpolateCamera>(m_Camera->GetTargetPos(), m_Camera->GetTargetLookPos(), m_Camera->GetOffsetPos(), m_Camera->GetOffsetLookPos());
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
	Enable(m_Camera->GetPos(), m_Camera->GetLookPos());
}


void CameraController::Reset()
{
	
}

void CameraController::Render2DDebug()
{
}

void CameraController::Quake(float power, float freq, float time)
{
	m_QuakePower = m_QuakePower > power ? m_QuakePower : power;
	m_QuakeFrequent = m_QuakeFrequent > freq ? m_QuakeFrequent : freq;
	if (m_QuakeTime <= 0.0f)
	{
		m_QuakeTime = time;
	}
}

void CameraController::Enable(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos;
	m_TargetLookPos = lookPos;
	//振動適用
	if (m_QuakeTime > 0.0f)
	{
		m_TargetPos.y += sinf(m_QuakeTime * m_QuakeFrequent) * m_QuakePower;
		m_TargetLookPos.y += sinf(m_QuakeTime * m_QuakeFrequent) * m_QuakePower;
		m_QuakeTime -= CUtilities::GetFrameSecond();
	}
	else
	{
		m_QuakeTime = 0;
		m_QuakeFrequent = 0;
		m_QuakePower = 0;
	}

	m_Camera->Enable(m_TargetPos, m_TargetLookPos);
}

