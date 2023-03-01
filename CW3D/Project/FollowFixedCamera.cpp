#include "FollowFixedCamera.h"

using namespace ActionGame;

CFollowFixedCamera::CFollowFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

CFollowFixedCamera::~CFollowFixedCamera()
{
	animationData_.Release();
}

void CFollowFixedCamera::Create()
{
	CameraBase::Create();
}

void CFollowFixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	targetPos_ = pos + offsetPos_;
	targetLookPos_ = lookPos + offsetLookPos_;
	position_ = targetPos_;
	lookPos_ = targetLookPos_;

}
