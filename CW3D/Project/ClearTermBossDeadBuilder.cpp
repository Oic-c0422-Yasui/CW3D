#include "ClearTermBossDeadBuilder.h"

ActionGame::ClearTermBossDeadBuilder::ClearTermBossDeadBuilder()
{
}

ActionGame::ClearTermPtr ActionGame::ClearTermBossDeadBuilder::Create(nlohmann::json& os)
{
    return Create();
}

ActionGame::ClearTermPtr ActionGame::ClearTermBossDeadBuilder::Create()
{
    ClearTermPtr result = std::make_shared<ClearTermBossDead>();
    return result;
}
