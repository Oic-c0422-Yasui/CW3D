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
    EnemyPtr enemy = std::make_shared<Enemy>();

    enemy->Load(param,
        m_ActionCreator,
        m_StateCreator,
        m_ParameterCreator,
        m_AiCreator);
    enemy->Initialize();

    return enemy;
}
