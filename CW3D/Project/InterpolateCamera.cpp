#include "InterpolateCamera.h"
#include "TimeScaleController.h"

using namespace ActionGame;

CInterpolateCamera::CInterpolateCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
	, targetOffsetLookPos_(0, 0, 0)
	, targetOffsetPos_(0, 0, 0)
	, posAnim_()
	, lookPosAnim_()
	, endTime_(0.0f)
	, currentTime_(0.0f)
{
}

CInterpolateCamera::~CInterpolateCamera()
{
	posAnim_.clear();
	lookPosAnim_.clear();
}

void CInterpolateCamera::Set(float time, MyUtil::EASING_TYPE ease, const CameraPtr& camera)
{
	Create();
	endTime_ = time;
	easeType_ = ease;
	targetOffsetLookPos_ = camera->GetOffsetLookPos();
	targetOffsetPos_ = camera->GetOffsetPos();
	Vector3 targetpos(camera->GetPosition());
	Vector3 targetLookPos(camera->GetLookPos());
	//切り替え前のカメラから切り替え後のカメラまでの座標のアニメーションを作成する
	MyUtil::ANIM_V3_DATA_ARRAY posAnim(
		{
			{0.0f,position_,easeType_},
			{endTime_,targetpos,easeType_},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY lookAnim(
		{
			{0.0f,lookPos_,easeType_},
			{endTime_,targetLookPos,easeType_},
		}
	);

	posAnim_ = posAnim;
	lookPosAnim_ = lookAnim;
	
}



void CInterpolateCamera::Create()
{
	currentTime_ = 0.0f;
	CameraBase::Create();
}

void CInterpolateCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	//現在地から目的地までの補間アニメーションを作成
	MyUtil::ANIM_V3_DATA_ARRAY posAnim(
		{
			{0.0f,position_,easeType_},
			{endTime_,pos + targetOffsetPos_,easeType_},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY lookAnim(
		{
			{0.0f,lookPos_,easeType_},
			{endTime_,lookPos + targetOffsetLookPos_,easeType_},
		}
	);

	//現在地から目的地までの座標で補間アニメーションを行う
	position_ = MyUtil::InterpolationAnim(currentTime_, posAnim);
	lookPos_ = MyUtil::InterpolationAnim(currentTime_, lookAnim);
	if (currentTime_ > endTime_)
	{
		isEndAnimation_ = true;
	}
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	CameraBase::UpdateCamera();
}

