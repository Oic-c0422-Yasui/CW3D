#include "NomalCamera.h"

using namespace ActionGame;

NomalCamera::NomalCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

NomalCamera::~NomalCamera()
{
}

void NomalCamera::Create()
{
	offsetLookPos_ = Vector3(0.0f, 1.0f, 0.0f);
	offsetPos_ = Vector3(0.0f, 5.0f, -15.0f);
	CameraBase::Create();
}

void NomalCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	//íxÇÍÇƒí«è]Ç∑ÇÈèàóù
	targetPos_ = pos + offsetPos_;
	position_.x += (targetPos_.x - position_.x) * 0.08f;
	position_.y += (targetPos_.y - position_.y) * 0.07f;
	position_.z += (targetPos_.z - position_.z) * 0.08f;
	targetLookPos_ = lookPos + offsetLookPos_;
	lookPos_.x += (targetLookPos_.x - lookPos_.x) * 0.12f;
	lookPos_.y += (targetLookPos_.y - lookPos_.y) * 0.11f;
	lookPos_.z += (targetLookPos_.z - lookPos_.z) * 0.12f;

	if (isReset_)
	{
		position_ = targetPos_;
		lookPos_ = targetLookPos_;
		isReset_ = false;
	}
}

void NomalCamera::Enable(const Vector3& pos, const Vector3& lookPos)
{
	targetPos_ = pos;
	lookPos_ = lookPos;
	position_ = pos;
	lookPos_ = lookPos;
	CameraBase::UpdateCamera();
}
