#include "Attack1StateBuilder.h"

ActionGame::Attack1StateBuilder::Attack1StateBuilder()
	:param_()
{
}

ActionGame::StatePtr ActionGame::Attack1StateBuilder::Create(nlohmann::json& os)
{
	os["armorLevel"].get_to(param_.armorLevel);
	os["colliderStartFrameTime"].get_to(param_.CollideStartTime);
	os["colliderEndFrameTime"].get_to(param_.CollideEndTime);
	os["nextInputFrameTime"].get_to(param_.NextInputTime);
	param_.ShotStatus = CreateAABBParam(os["colliderParam"]);
	param_.EffectStatus = CreateEffectParam(os["effectParam"]);

	return Create();
}

ActionGame::StatePtr ActionGame::Attack1StateBuilder::Create()
{
	auto state = std::make_shared<CAttack1State>(param_);

	return state;
}
