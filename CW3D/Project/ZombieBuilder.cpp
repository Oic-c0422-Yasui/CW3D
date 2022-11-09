#include "ZombieBuilder.h"
#include "ZombieActionCreator.h"
#include "ZombieAICreator.h"
#include "ZombieStateCreator.h"
#include "ZombieParameterCreator.h"

using namespace Sample;

Sample::ZombieBuilder::ZombieBuilder()
    : EnemyBuilder(std::make_shared<ZombieActionCreator>(),
                    std::make_shared<ZombieStateCreator>(),
                    std::make_shared<ZombieParameterCreator>(),
                    std::make_shared<ZombieAICreator>())

{
}



EnemyPtr Sample::ZombieBuilder::Create(const EnemyBuildParameter& param)
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
