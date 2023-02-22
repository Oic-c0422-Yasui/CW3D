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
	, currentTime_(0.0f)
	, m_TempLeapEndTime(0.0f)
	, time_(0.0f)
	, m_QuakePower(0.0f)
	, m_QuakeFrequent(0.0f)
	, m_QuakeTime(0.0f)
	, m_QuakeCurrentTime(0.0f)
	, targetPos_(0,0,0)
	, targetLookPos_(0,0,0)
	
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
	camera_ = camera;
	camera_->Create();
	CGraphicsUtilities::SetCamera(&camera_->GetCamera());
}

void CameraController::SetCamera(const CameraPtr& camera, float tTime)
{
	SetCamera(camera);
	time_ = tTime;
	currentTime_ = 0.0f;
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

void CameraController::SetCamera(const CameraPtr& camera, float tTime, MyUtil::EASING_TYPE startEaseType, float leapStartTime, MyUtil::EASING_TYPE endEaseType,float leapEndTime)
{
	InterpolateCameraPtr pCamera = std::make_shared<CInterpolateCamera>(camera_->GetTargetPos(), camera_->GetTargetLookPos(), camera_->GetOffsetPos(), camera_->GetOffsetLookPos());
	pCamera->Set(leapStartTime,startEaseType, camera);
	camera_ = pCamera;
	SetCamera(camera_);
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
	m_DefaultCamera->SetIsReset(true);
	SetCamera(m_DefaultCamera);
}

void CameraController::Update(const Vector3& pos, const Vector3& lookPos)
{
	if (m_LeapStartFlg)
	{
		if (camera_->IsEnd())
		{
			SetCamera(m_NextCamera, m_LeapTime);
		}
	}
	//タイマー
	if (m_TimerStartFlg)
	{
		if (time_ > currentTime_)
		{
			currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
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
				InterpolateCameraPtr pCamera = std::make_shared<CInterpolateCamera>(camera_->GetTargetPos(), camera_->GetTargetLookPos(), camera_->GetOffsetPos(), camera_->GetOffsetLookPos());
				m_DefaultCamera->SetPos(pos + m_DefaultCamera->GetOffsetPos());
				m_DefaultCamera->SetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());
				m_DefaultCamera->SetTargetPos(pos + m_DefaultCamera->GetOffsetPos());
				m_DefaultCamera->SetTargetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());

				pCamera->Set(m_TempLeapEndTime, m_EndEaseType, m_DefaultCamera);
				camera_ = pCamera;
				SetCamera(camera_);
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
		if (camera_->IsEnd())
		{
			m_DefaultCamera->SetPos(pos + m_DefaultCamera->GetOffsetPos());
			m_DefaultCamera->SetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());
			m_DefaultCamera->SetTargetPos(pos + m_DefaultCamera->GetOffsetPos());
			m_DefaultCamera->SetTargetLookPos(lookPos + m_DefaultCamera->GetOffsetLookPos());
			SetDefault();
			m_LeapEndFlg = false;
		}
	}
	camera_->Update(pos, lookPos);
	Enable(camera_->GetPosition(), camera_->GetLookPos());
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
	targetPos_ = pos;
	targetLookPos_ = lookPos;
	//振動適用
	if (m_QuakeTime > 0.0f)
	{
		targetPos_.y += sinf(m_QuakeTime * m_QuakeFrequent) * m_QuakePower;
		targetLookPos_.y += sinf(m_QuakeTime * m_QuakeFrequent) * m_QuakePower;
		m_QuakeTime -= CUtilities::GetFrameSecond();
	}
	else
	{
		m_QuakeTime = 0;
		m_QuakeFrequent = 0;
		m_QuakePower = 0;
	}

	camera_->Enable(targetPos_, targetLookPos_);
}

