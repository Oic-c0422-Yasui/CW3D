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



EnemyPtr ActionGame::ZombieBuilder::Create(const EnemyBuildParameterPtr& param)
{
    
    EnemyPtr enemy = std::make_shared<CEnemy>();

    enemy->Load(param,
        m_ActionCreator,
        m_StateCreator,
        m_ParameterCreator,
        m_AiCreator);
    enemy->Initialize();

    return enemy;
}
