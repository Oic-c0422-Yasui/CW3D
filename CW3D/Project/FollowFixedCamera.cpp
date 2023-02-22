#include "FollowFixedCamera.h"

using namespace ActionGame;

FollowFixedCamera::FollowFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

FollowFixedCamera::~FollowFixedCamera()
{
	animationData_.Release();
}

void FollowFixedCamera::Create()
{
	CameraBase::Create();
}

void FollowFixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	targetPos_ = pos + offsetPos_;
	targetLookPos_ = lookPos + offsetLookPos_;
	position_ = targetPos_;
	lookPos_ = targetLookPos_;

}
