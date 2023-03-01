#include "ClearTermBossDeadBuilder.h"

ClearTerm::CBossDeadBuilder::CBossDeadBuilder()
{
}

ClearTerm::ClearTermPtr ClearTerm::CBossDeadBuilder::Create(nlohmann::json& os)
{
    return Create();
}

ClearTerm::ClearTermPtr ClearTerm::CBossDeadBuilder::Create()
{
    ClearTermPtr result = std::make_shared<CBossDead>();
    return result;
}
