#include "MutantBuilder.h"
#include "MutantActionCreator.h"
#include "MutantAICreator.h"
#include "MutantParameterCreator.h"
#include "MutantStateCreator.h"

ActionGame::MutantBuilder::MutantBuilder()
    : EnemyBuilder(std::make_shared<MutantActionCreator>(),
        std::make_shared<MutantStateCreator>(),
        std::make_shared<MutantParameterCreator>(),
        std::make_shared<MutantAICreator>())

{
}

ActionGame::EnemyPtr ActionGame::MutantBuilder::Create(const EnemyBuildParameterPtr& param)
{
    EnemyPtr enemy = std::make_shared<CEnemy>();

    enemy->Load(param,
        actionCreator_,
        stateCreator_,
        parameterCreator_,
        AICreator_);
    enemy->Initialize();

    return enemy;
}
