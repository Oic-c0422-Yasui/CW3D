#include "IdleStateBuilder.h"

ActionGame::IdleStateBuilder::IdleStateBuilder()
{
}

ActionGame::StatePtr ActionGame::IdleStateBuilder::Create(nlohmann::json& os)
{
	return StatePtr();
}

ActionGame::StatePtr ActionGame::IdleStateBuilder::Create()
{
	return StatePtr();
}
