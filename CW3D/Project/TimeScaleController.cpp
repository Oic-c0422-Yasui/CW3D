#include	"TimeScaleController.h"

void ActionGame::TimeScaleController::Update()
{
	timeScale_.Update();
	for (auto& chara : charaMap_)
	{
		chara.second.Update();
	}
}

float ActionGame::TimeScaleController::GetTimeScale(CHARA_TYPE type) noexcept
{
	auto it = charaMap_.find(type);
	if (it != charaMap_.end())
	{
		return min(charaMap_[type].GetScale(), timeScale_.GetScale());
	}

	return timeScale_.GetScale();
}

void ActionGame::TimeScaleController::Reset() noexcept
{
	timeScale_.Reset();
	for (auto& chara : charaMap_)
	{
		chara.second.Reset();
	}
}

void ActionGame::TimeScaleController::SetTimeScale(CHARA_TYPE type, float scale, float changeTime, MyUtil::EASING_TYPE easeType) noexcept
{
	auto it = charaMap_.find(type);
	if (it != charaMap_.end())
	{
		charaMap_[type].SetScale(scale, changeTime, easeType);
	}
}

void ActionGame::TimeScaleController::SetTimeScale(CHARA_TYPE type, const MyUtil::ANIM_DATA_ARRAY& anim) noexcept
{
	auto it = charaMap_.find(type);
	if (it != charaMap_.end())
	{
		charaMap_[type].SetScale(anim);
	}
}

void ActionGame::TimeScaleController::SetOtherTimeScale(CHARA_TYPE type, float scale, float changeTime, MyUtil::EASING_TYPE easeType) noexcept
{
	for (auto& chara : charaMap_)
	{
		if (chara.first == type)
		{
			continue;
		}
		//引数のtype以外のタイムスケールを変更する
		chara.second.SetScale(scale, changeTime, easeType);
	}

}

void ActionGame::TimeScaleController::SetOtherTimeScale(CHARA_TYPE type, const MyUtil::ANIM_DATA_ARRAY& anim) noexcept
{
	for (auto& chara : charaMap_)
	{
		if (chara.first == type)
		{
			continue;
		}
		//引数のtype以外のタイムスケールを変更する
		chara.second.SetScale(anim);
	}
}
