#include "FixedCamera.h"
#include "TimeScaleController.h"

using namespace ActionGame;

CFixedCamera::CFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

CFixedCamera::~CFixedCamera()
{
	animationData_.Release();
}

void CFixedCamera::Create()
{
	CameraBase::Create();
}

void CFixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{

	if (animationData_.isAnimation)
	{
		auto& anim = animationData_;
		offsetPos_ = MyUtil::InterpolationAnim(anim.currentTime, anim.posAnim);
		offsetLookPos_ = MyUtil::InterpolationAnim(anim.currentTime, anim.lookPosAnim);
		anim.currentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	position_	= targetPos_ + offsetPos_;
	lookPos_	= targetLookPos_ + offsetLookPos_;

	CameraBase::UpdateCamera();
}
