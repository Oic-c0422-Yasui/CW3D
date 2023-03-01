#include "TimeScale.h"

ActionGame::CTimeScale::CTimeScale()
	: timeScale_(1.0f)
	, isChange_(false)
	, changeTime_(0.0f)
	, currentTime_(0.0f)
	, animDataArray_()
{
}

void ActionGame::CTimeScale::Update()
{
	if (!isChange_)
	{
		return;
	}
	if (changeTime_ > currentTime_)
	{
		currentTime_ += CUtilities::GetFrameSecond();
	}
	else
	{
		isChange_ = false;
	}
	timeScale_ = MyUtil::InterpolationAnim(currentTime_, animDataArray_);
}

void ActionGame::CTimeScale::SetScale(float scale, float changeTime, MyUtil::EASING_TYPE easeType) noexcept
{
	MyUtil::ANIM_DATA_ARRAY anim(
		{
			{0, timeScale_, easeType},
			{changeTime, scale, easeType}
		}
	);

	animDataArray_ = anim;
	currentTime_ = 0.0f;
	changeTime_ = changeTime;
	isChange_ = true;
}


void ActionGame::CTimeScale::SetScale(const MyUtil::ANIM_DATA_ARRAY& anim)
{
	animDataArray_ = anim;
	changeTime_ = animDataArray_.back().Time;
	currentTime_ = 0.0f;
	isChange_ = true;
}

void ActionGame::CTimeScale::Reset() noexcept
{
	timeScale_ = 1.0f;
	currentTime_ = 0.0f;
	changeTime_ = 0.0f;
	isChange_ = false;
}
