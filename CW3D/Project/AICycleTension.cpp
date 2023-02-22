#include "AICycleTension.h"
#include "TimeScaleController.h"

ActionGame::AICycleTension::AICycleTension(ActorPtr actor)
	: actor_(actor)
	, currentTime_(0)
{
}

bool ActionGame::AICycleTension::Update()
{
	//プレイヤー取得
	const auto& player = ServiceLocator< CPlayer >::GetService();
	const auto& transform = actor_->GetTransform();
	//距離からインターバル算出
	float sx = player->GetPosition().x - transform->GetPosition().x;
	float sz = player->GetPosition().z - transform->GetPosition().z;
	float d = sqrt(sx * sx + sz * sz);
	int interval = (int)((d - 30.0f) / 20.0f);
	interval = interval <= 0 ? 1 : interval;
	currentTime_ += 1;
	if (currentTime_ > interval)
	{
		currentTime_ -= interval;
		return true;
	}
	return false;
}
