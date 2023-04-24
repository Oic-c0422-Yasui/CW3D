#include "RevivalCount.h"

ActionGame::CRevivalCount::CRevivalCount(uint32_t maxCount)
	: currentCount_(maxCount)
	, maxCount_(maxCount)
{
}

ActionGame::CRevivalCount::~CRevivalCount()
{
}

uint32_t ActionGame::CRevivalCount::GetCurrentCount() const noexcept
{
	return currentCount_;
}

uint32_t ActionGame::CRevivalCount::GetMaxCount() const noexcept
{
	return maxCount_;
}

void ActionGame::CRevivalCount::SubCount() noexcept
{
	if (currentCount_ <= 0){ return;}
	currentCount_--;
}

void ActionGame::CRevivalCount::Reset()
{
	currentCount_ = maxCount_;
}
