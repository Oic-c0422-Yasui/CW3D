#include "FixedCamera.h"
#include "TimeScaleController.h"

using namespace ActionGame;

FixedCamera::FixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

FixedCamera::~FixedCamera()
{
	animationData_.Release();
}

void FixedCamera::Create()
{
	CameraBase::Create();
}

void FixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
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
