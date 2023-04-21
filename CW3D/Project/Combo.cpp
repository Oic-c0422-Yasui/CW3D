#include "Combo.h"

ActionGame::CCombo::CCombo(float resetTime)
	: count_(0)
	, resetTime_(resetTime)
	, timer_()
{
}

void ActionGame::CCombo::Initialize()
{
	count_ .Set(0);
	timer_.Start(resetTime_);
}


void ActionGame::CCombo::Update(CHARA_TYPE type)
{

	if (timer_.IsAchieve() && count_.operator>(0))
	{
		//リセット
		Initialize();
	}
	else if (count_.operator>(0))
	{
		//タイマー更新
		timer_.Update(type);
	}
}

uint32_t ActionGame::CCombo::GetCount() const noexcept
{
	return count_;
}

ActionGame::CReactiveParameter<uint32_t>& ActionGame::CCombo::GetCountParam() noexcept
{
	return count_;
}


ActionGame::IObservable<float>& ActionGame::CCombo::GetTimeSubject()
{
	return timer_.GetTimeSubject();
}

void ActionGame::CCombo::AddCount() noexcept
{
	count_ .operator+=(1);
	timer_.Reset();
}

