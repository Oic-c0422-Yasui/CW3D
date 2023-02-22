#include "Velocity.h"

ActionGame::CVelocity::CVelocity()
	: velocity_(0.0f, 0.0f, 0.0f)
	, maxVelocity_(0.0f, 0.0f, 0.0f)
	, updateVelocity_(0.0f, 0.0f, 0.0f)
	, decelerate_(0.0f, 0.0f, 0.0f)
	, isUseGravity_(true)
	, gravity_(0.0f)
	, isSetRotate_(false)
	, currentTime_(0.0f)
	, moveTime_(0.0f)
	, targetY_(0.0f)
	, startY_(0.0f)
	, currentY_(0.0f)
	, type_()
{
}

void ActionGame::CVelocity::Update()
{
	//重力の適用
	if (isUseGravity_)
	{
		velocity_.y -= gravity_ * TimeScaleControllerInstance.GetTimeScale(type_);
		velocity_.y = ((velocity_.y < -maxVelocity_.y) ?
			-maxVelocity_.y : velocity_.y);
	}

	//回転の更新
	if (isSetRotate_)
	{
		if (currentTime_ <= moveTime_)
		{
			currentY_ = MyUtil::RotateTimer(startY_, currentTime_, targetY_, moveTime_);

			currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(type_);
		}
		else
		{
			currentY_ = targetY_;
			isSetRotate_ = false;
		}
	}
	//速度の更新を実施
	if (fabsf(updateVelocity_.x) > 0)
	{
		//最大速度を超えるようなら倍速で減速
		if (velocity_.x > maxVelocity_.x + decelerate_.x * 2 * TimeScaleControllerInstance.GetTimeScale(type_))
		{
			velocity_.x -= decelerate_.x * 2 * TimeScaleControllerInstance.GetTimeScale(type_);
			if (updateVelocity_.x < 0)
			{
				velocity_.x += updateVelocity_.x * TimeScaleControllerInstance.GetTimeScale(type_);
			}
		}
		else if (velocity_.x < -maxVelocity_.x - decelerate_.x * 2 * TimeScaleControllerInstance.GetTimeScale(type_))
		{
			velocity_.x += decelerate_.x * 2 * TimeScaleControllerInstance.GetTimeScale(type_);
			if (updateVelocity_.x > 0)
			{
				velocity_.x += updateVelocity_.x * TimeScaleControllerInstance.GetTimeScale(type_);
			}
		}
		else
		{
			velocity_.x += updateVelocity_.x * TimeScaleControllerInstance.GetTimeScale(type_);
			velocity_.x = ((velocity_.x > maxVelocity_.x) ?
				maxVelocity_.x : ((velocity_.x < -maxVelocity_.x) ?
					-maxVelocity_.x : velocity_.x));
		}
		updateVelocity_.x = 0;
	}
	else
	{
		velocity_.x = ((fabsf(velocity_.x) < fabsf(decelerate_.x)) ?
			0 : velocity_.x - copysignf(decelerate_.x, velocity_.x));
	}
	if (fabsf(updateVelocity_.z) > 0)
	{
		//最大速度を超えるようなら倍速で減速
		if (velocity_.z > maxVelocity_.z + decelerate_.z * 2 * TimeScaleControllerInstance.GetTimeScale(type_))
		{
			velocity_.z -= decelerate_.z * 2 * TimeScaleControllerInstance.GetTimeScale(type_);
			if (updateVelocity_.z < 0)
			{
				velocity_.z += updateVelocity_.z * TimeScaleControllerInstance.GetTimeScale(type_);
			}
		}
		else if (velocity_.z < -maxVelocity_.z - decelerate_.z * 2 * TimeScaleControllerInstance.GetTimeScale(type_))
		{
			velocity_.z += decelerate_.z * 2 * TimeScaleControllerInstance.GetTimeScale(type_);
			if (updateVelocity_.z > 0)
			{
				velocity_.z += updateVelocity_.z * TimeScaleControllerInstance.GetTimeScale(type_);
			}
		}
		else
		{
			velocity_.z += updateVelocity_.z * TimeScaleControllerInstance.GetTimeScale(type_);
			velocity_.z = ((velocity_.z > maxVelocity_.z) ?
				maxVelocity_.z : ((velocity_.z < -maxVelocity_.z) ?
					-maxVelocity_.z : velocity_.z));
		}
		updateVelocity_.z = 0;
	}
	else
	{
		velocity_.z = ((fabsf(velocity_.z) < fabsf(decelerate_.z)) ?
			0 : velocity_.z - copysignf(decelerate_.z, velocity_.z));
	}
}
