#include "MutantBuilder.h"
#include "MutantActionCreator.h"
#include "MutantAICreator.h"
#include "MutantParameterCreator.h"
#include "MutantStateCreator.h"
#include "MutantSkillCreator.h"

ActionGame::MutantBuilder::MutantBuilder()
    : EnemyBuilder(std::make_shared<MutantActionCreator>(),
        std::make_shared<MutantStateCreator>(),
        std::make_shared<MutantParameterCreator>(),
        std::make_shared<MutantAICreator>(),
        std::make_shared<MutantSkillCreator>())

{
}

ActionGame::EnemyPtr ActionGame::MutantBuilder::Create(const EnemyBuildParameterPtr& param)
{
    EnemyPtr enemy = std::make_shared<CEnemy>();

    enemy->Load(param,
        actionCreator_,
        stateCreator_,
        parameterCreator_,
        AICreator_,
        skillCreator_);
    enemy->Initialize();

    return enemy;
}
