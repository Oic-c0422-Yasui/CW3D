#include "Revival.h"

ActionGame::CRevival::CRevival()
	: count_(nullptr)
{
}

ActionGame::CRevival::~CRevival()
{
}

bool ActionGame::CRevival::Load(uint32_t revivalCount)
{
	count_ = std::make_shared<CRevivalCount>(revivalCount);


	return true;
}

void ActionGame::CRevival::Initialize()
{
	count_->Reset();
}

void ActionGame::CRevival::SubCount() noexcept
{
	count_->SubCount();
}

uint32_t ActionGame::CRevival::GetCount() const noexcept
{
	return count_->GetCurrentCount();
}
