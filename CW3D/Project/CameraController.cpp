#include "CameraController.h"
#include "InterpolateCamera.h"
#include "TimeScaleController.h"


using namespace ActionGame;

CCameraController::CCameraController()
	: Singleton<CCameraController>()
	, isTimerStart_(false)
	, isLeap_(false)
	, isLeapStart_(false)
	, isLeapEnd_(false)
	, leapTime_(0.0f)
	, currentTime_(0.0f)
	, leapEndTime_(0.0f)
	, timeScale_(0.0f)
	, quakeState_()
	, targetPos_(0,0,0)
	, targetLookPos_(0,0,0)
	
{
}



CCameraController::~CCameraController()
{
}

void CCameraController::Load(const CameraPtr& camera)
{
	defaultCamera_ = camera;
	SetDefault();
}

void CCameraController::SetCamera(const CameraPtr& camera)
{
	camera_ = camera;
	camera_->Create();
	CGraphicsUtilities::SetCamera(&camera_->GetCamera());
}

void CCameraController::SetCamera(const CameraPtr& camera, float tTime)
{
	SetCamera(camera);
	timeScale_ = tTime;
	currentTime_ = 0.0f;
	isTimerStart_ = true;
	if (!isLeapStart_)
	{
		isLeap_ = false;
		isLeapEnd_ = false;
	}
	else
	{
		isLeapStart_ = false;
	}
}

void CCameraController::SetCamera(const CameraPtr& camera, float tTime, MyUtil::EASING_TYPE startEaseType, float leapStartTime, MyUtil::EASING_TYPE endEaseType,float leapEndTime)
{
	InterpolateCameraPtr pCamera = std::make_shared<CInterpolateCamera>(
		camera_->GetTargetPos(), camera_->GetTargetLookPos(), camera_->GetOffsetPos(), camera_->GetOffsetLookPos());
	pCamera->Set(leapStartTime,startEaseType, camera);
	camera_ = pCamera;
	SetCamera(camera_);
	isLeap_ = true;
	isTimerStart_ = false;
	nextCamera_ = camera;
	leapTime_ = tTime;
	isLeapStart_ = true;
	isLeapEnd_ = false;
	leapEndTime_ = leapEndTime;
	endEaseType_ = endEaseType;
	pCamera.reset();
}

void CCameraController::SetDefault()
{
	isLeapStart_ = false;
	isLeap_ = false;
	isLeapEnd_ = false;
	isTimerStart_ = false;
	defaultCamera_->SetIsReset(true);
	SetCamera(defaultCamera_);
}

void CCameraController::Update(const Vector3& pos, const Vector3& lookPos)
{
	if (isLeapStart_)
	{
		if (camera_->IsEnd())
		{
			SetCamera(nextCamera_, leapTime_);
		}
	}
	//タイマー
	if (isTimerStart_)
	{
		if (timeScale_ > currentTime_)
		{
			currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
		}
		else
		{
			//タイマー終了時
			
			isTimerStart_ = false;
			//補間フラグがTrueなら
			if (isLeap_)
			{
				isLeap_ = false;
				isLeapEnd_ = true;
				InterpolateCameraPtr pCamera = std::make_shared<CInterpolateCamera>(camera_->GetTargetPos(), camera_->GetTargetLookPos(), camera_->GetOffsetPos(), camera_->GetOffsetLookPos());
				defaultCamera_->SetPos(pos + defaultCamera_->GetOffsetPos());
				defaultCamera_->SetLookPos(lookPos + defaultCamera_->GetOffsetLookPos());
				defaultCamera_->SetTargetPos(pos + defaultCamera_->GetOffsetPos());
				defaultCamera_->SetTargetLookPos(lookPos + defaultCamera_->GetOffsetLookPos());

				pCamera->Set(leapEndTime_, endEaseType_, defaultCamera_);
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
	if (isLeapEnd_)
	{
		if (camera_->IsEnd())
		{
			defaultCamera_->SetPos(pos + defaultCamera_->GetOffsetPos());
			defaultCamera_->SetLookPos(lookPos + defaultCamera_->GetOffsetLookPos());
			defaultCamera_->SetTargetPos(pos + defaultCamera_->GetOffsetPos());
			defaultCamera_->SetTargetLookPos(lookPos + defaultCamera_->GetOffsetLookPos());
			SetDefault();
			isLeapEnd_ = false;
		}
	}
	camera_->Update(pos, lookPos);
	Enable(camera_->GetPosition(), camera_->GetLookPos());
}


void CCameraController::Reset()
{
	
}

void CCameraController::Render2DDebug()
{
}

void CCameraController::Quake(float power, float freq, float time)
{
	quakeState_.power = quakeState_.power > power ? quakeState_.power : power;
	quakeState_.frequent = quakeState_.frequent > freq ? quakeState_.frequent : freq;
	if (quakeState_.time <= 0.0f)
	{
		quakeState_.time = time;
	}
}

void CCameraController::Enable(const Vector3& pos, const Vector3& lookPos)
{
	targetPos_ = pos;
	targetLookPos_ = lookPos;
	//振動適用
	if (quakeState_.time > 0.0f)
	{
		targetPos_.y += sinf(quakeState_.time * quakeState_.frequent) * quakeState_.power;
		targetLookPos_.y += sinf(quakeState_.time * quakeState_.frequent) * quakeState_.power;
		quakeState_.time -= CUtilities::GetFrameSecond();
	}
	else
	{
		quakeState_.time = 0;
		quakeState_.frequent = 0;
		quakeState_.power = 0;
	}

	camera_->Enable(targetPos_, targetLookPos_);
}

