#include "SceneChangeFade.h"

Scene::SceneChangeFade::SceneChangeFade(float startTime, float durationTime, float endTime)
	: currentTime_(0.0f)
	, startTime_(startTime)
	, durationTime_(durationTime)
	, endTime_(endTime)
	, isHalfPoint_(false)
	, alpha_(0)
{
	totalTime_ = startTime_ + durationTime_ + endTime_;
}

void Scene::SceneChangeFade::Update()
{
	currentTime_ += CUtilities::GetFrameSecond();
	if (!IsHalfPoint())
	{
		float rate = currentTime_ / startTime_;
		//フェードイン
		alpha_ = (int)(255 * rate);
	}
	else if(currentTime_ >= startTime_ + durationTime_)
	{
		float rate = currentTime_ / totalTime_;
		//フェードアウト
		alpha_ = (int)(255 * (1 - rate));
	}
}

void Scene::SceneChangeFade::Render(ScenePtr& prev, ScenePtr& current)
{
	CRectangle rect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());
	CGraphicsUtilities::RenderFillRect(rect, MOF_ARGB(alpha_, 0, 0, 0));
}

bool Scene::SceneChangeFade::IsEnd() const noexcept
{
	return currentTime_ >= totalTime_;
}

bool Scene::SceneChangeFade::IsHalfPoint() const noexcept
{
	return currentTime_ >= startTime_;
}
