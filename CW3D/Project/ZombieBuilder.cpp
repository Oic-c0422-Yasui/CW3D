#include "ZombieBuilder.h"

using namespace Sample;

Sample::ZombieBuilder::ZombieBuilder(const ActionCreatorPtr&        actionCreator,
                                     const StateCreatorPtr&         stateCreator,
                                     const ParameterCreatorPtr&     parameterCreator,
                                     const CharacterAICreatorPtr&   aiCreator)
    : m_ActionCreator(actionCreator)
    , m_StateCreator(stateCreator)
    , m_ParameterCreator(parameterCreator)
    , m_AiCreator(aiCreator)
{
}

const EnemyPtr& Sample::ZombieBuilder::Create(const EnemyBuildParameter& param)
{
    
    EnemyPtr enemy = std::make_shared<CEnemy>();

    enemy->Load(param.GetParam().m_Pos,
        m_ActionCreator,
        m_StateCreator,
        m_ParameterCreator,
        m_AiCreator);
    enemy->Initialize();

    return enemy;
}
