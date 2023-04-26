#include "Velocity.h"



ActionGame::CVelocity::CVelocity()
	: velocity_(0.0f, 0.0f, 0.0f)
	, maxVelocity_(0.0f, 0.0f, 0.0f)
	, updateVelocity_(0.0f, 0.0f, 0.0f)
	, decelerate_(0.0f, 0.0f, 0.0f)
	, isUseGravity_(true)
	, gravity_(0.0f)
	, gravityScale_()
	, rotate_()
	, type_()
{
	gravityScale_.currentScale = 1.0f;
}

void ActionGame::CVelocity::Update()
{
	//重力の適用
	UpdateGravity();

	//回転の更新
	UpdateRotate();

	//速度の更新を実施
	UpdateVelocity();
}

void ActionGame::CVelocity::UpdateRotate()
{
	if (!rotate_.isStart)
	{
		return;
	}

	if (rotate_.currentTime <= rotate_.endTime)
	{
		rotate_.currentY = MyUtil::RotateTimer(rotate_.startY, rotate_.currentTime,
							rotate_.targetY, rotate_.endTime);

		rotate_.currentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(type_);
	}
	else
	{
		rotate_.currentY = rotate_.targetY;
		rotate_.isStart = false;
	}
}

void ActionGame::CVelocity::UpdateGravityScale()
{
	if (!gravityScale_.isStart)
	{
		return;
	}

	if (gravityScale_.currentTime <= gravityScale_.endTime)
	{
		gravityScale_.currentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(type_);
	}
	else
	{
		gravityScale_.currentScale = gravityScale_.targetScale;
		gravityScale_.isStart = false;
	}
}

void ActionGame::CVelocity::UpdateGravity()
{
	if (!isUseGravity_)
	{
		return;
	}
	UpdateGravityScale();

	auto scale = TimeScaleControllerInstance.GetTimeScale(type_);
	velocity_.y -= (velocity_.y > 0.0f) ?
		gravity_ * scale :
		gravity_ * gravityScale_.currentScale * scale;
	
	velocity_.y = ((velocity_.y < -maxVelocity_.y) ?
		-maxVelocity_.y : velocity_.y);
}



void ActionGame::CVelocity::UpdateVelocity()
{
	auto scale = TimeScaleControllerInstance.GetTimeScale(type_);

	if (fabsf(updateVelocity_.x) > 0)
	{
		//最大速度を超えるようなら倍速で減速
		if (velocity_.x > maxVelocity_.x + decelerate_.x * 2 * scale)
		{
			velocity_.x -= decelerate_.x * 2 * scale;
			if (updateVelocity_.x < 0)
			{
				velocity_.x += updateVelocity_.x * scale;
			}
		}
		else if (velocity_.x < -maxVelocity_.x - decelerate_.x * 2 * scale)
		{
			velocity_.x += decelerate_.x * 2 * scale;
			if (updateVelocity_.x > 0)
			{
				velocity_.x += updateVelocity_.x * scale;
			}
		}
		else
		{
			velocity_.x += updateVelocity_.x * scale;
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
		if (velocity_.z > maxVelocity_.z + decelerate_.z * 2 * scale)
		{
			velocity_.z -= decelerate_.z * 2 * scale;
			if (updateVelocity_.z < 0)
			{
				velocity_.z += updateVelocity_.z * scale;
			}
		}
		else if (velocity_.z < -maxVelocity_.z - decelerate_.z * 2 * scale)
		{
			velocity_.z += decelerate_.z * 2 * scale;
			if (updateVelocity_.z > 0)
			{
				velocity_.z += updateVelocity_.z * scale;
			}
		}
		else
		{
			velocity_.z += updateVelocity_.z * scale;
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
