#include "Transform.h"


ActionGame::CTransform::CTransform()
	: position_(0, 0, 0)
	, scale_(1, 1, 1)
	, rotate_(0, 0, 0)
	, world_()
	, isUpdate_(false)
	, isReverse_(false)
	, type_()
{
}

void ActionGame::CTransform::UpdateMatrix()
{
	CMatrix44 matScale;
	CMatrix44 matRotate;
	matScale.Scaling(scale_);
	matRotate.RotationZXY(rotate_);
	world_ = matScale * matRotate;

	world_.SetTranslation(position_);

	//world_ *= parent->GetWorld();
}


void ActionGame::CTransform::AddPosition(const Vector3& position) noexcept
{
	position_ += position * TimeScaleControllerInstance.GetTimeScale(type_);
	world_.SetTranslation(position_);
}

void ActionGame::CTransform::AddPosition(const VelocityPtr& velocity) noexcept
{
	if (velocity->IsGravity())
	{
		position_ += velocity->GetVelocity() * TimeScaleControllerInstance.GetTimeScale(type_);
	}
	else
	{
		position_.x += velocity->GetVelocityX() * TimeScaleControllerInstance.GetTimeScale(type_);
		position_.z += velocity->GetVelocityZ() * TimeScaleControllerInstance.GetTimeScale(type_);
	}
	world_.SetTranslation(position_);
}

void ActionGame::CTransform::Clip(const Vector3& min, const Vector3& max)
{
	ClipX(min.x, max.x);
	ClipY(min.y, max.y);
	ClipZ(min.z, max.z);
}

void ActionGame::CTransform::ClipX(float min, float max)
{
	position_.x = ((position_.x > max) ?
		max : ((position_.x < min) ? min : position_.x));
}

void ActionGame::CTransform::ClipY(float min, float max)
{
	position_.y = ((position_.y > max) ?
		max : ((position_.y < min) ? min : position_.y));
}

void ActionGame::CTransform::ClipZ(float min, float max)
{
	position_.z = ((position_.z > max) ?
		max : ((position_.z < min) ? min : position_.z));
}

void ActionGame::CTransform::SetPosition(const Vector3& position) noexcept
{
	position_ = position;
	world_.SetTranslation(position_);
}
