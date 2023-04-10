#include "Timer.h"

ActionGame::CTimer::CTimer()
	: currentTime_(0.0f)
	, targetTime_(0.0f)
	, isAchieve_(false)
	, isStop_(false)
{
}

ActionGame::CTimer::~CTimer()
{
}

void ActionGame::CTimer::Start()
{
	currentTime_ = 0.0f;
	targetTime_ = 0.0f;
	isAchieve_ = false;
	isStop_ = false;
}

void ActionGame::CTimer::Start(float targetTime)
{
	Start();
	targetTime_ = targetTime;
}

void ActionGame::CTimer::Stop()
{
	isStop_ = true;
}

void ActionGame::CTimer::Update()
{
	if (isStop_)
	{
		return;
	}
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	if (currentTime_ >= targetTime_)
	{
		if (!isAchieve_)
		{
			isAchieve_ = true;
		}
	}
}

void ActionGame::CTimer::Update(CHARA_TYPE timeScaleType)
{
	if (isStop_)
	{
		return;
	}
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(timeScaleType);
	if (currentTime_ >= targetTime_)
	{
		if (!isAchieve_)
		{
			isAchieve_ = true;
		}
	}
}

void ActionGame::CTimer::Reset()
{
	currentTime_ = 0.0f;
	isAchieve_ = false;
	isStop_ = false;
}
