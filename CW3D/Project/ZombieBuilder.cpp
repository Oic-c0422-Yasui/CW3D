#include "ZombieBuilder.h"
#include "ZombieActionCreator.h"
#include "ZombieAICreator.h"
#include "ZombieStateCreator.h"
#include "ZombieParameterCreator.h"

using namespace ActionGame;

ActionGame::ZombieBuilder::ZombieBuilder()
    : EnemyBuilder(std::make_shared<ZombieActionCreator>(),
                    std::make_shared<ZombieStateCreator>(),
                    std::make_shared<ZombieParameterCreator>(),
                    std::make_shared<ZombieAICreator>())

{
}



ActionGame::EnemyPtr ActionGame::ZombieBuilder::Create(const EnemyBuildParameterPtr& param)
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
