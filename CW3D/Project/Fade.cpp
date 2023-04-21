#include "Fade.h"
#include "TimeScaleController.h"

ActionGame::CFade::CFade()
	: currentValue_(0)
	, startValue_(0)
	, endValue_(0)
	, isStart_(false)
	, timer_()
{
}

ActionGame::CFade::~CFade()
{
}

void ActionGame::CFade::Initialize(BYTE startValue, float endTime, BYTE endValue)
{
	startValue_ = startValue;
	endValue_ = endValue;
	currentValue_ = startValue_;
	endTime_ = endTime;
	isStart_ = false;

}

void ActionGame::CFade::Start()
{
	timer_.Start(endTime_);
	isStart_ = true;
	currentValue_ = startValue_;
}

void ActionGame::CFade::Update()
{
	if (!isStart_ || timer_.IsAchieve())
	{
		return;
	}

	auto time = timer_.GetTime();
	auto endTime = timer_.GetTargetTime();
	currentValue_ = MyUtil::Timer(startValue_, time, endValue_, endTime);

	timer_.Update();
}

void ActionGame::CFade::Reset()
{
	currentValue_ = startValue_;
	timer_.Reset();
	isStart_ = false;
}



BYTE ActionGame::CFade::GetFadeValue() const noexcept
{
	return currentValue_;
}

bool ActionGame::CFade::IsEnd() const noexcept
{
	return timer_.IsAchieve();
}
