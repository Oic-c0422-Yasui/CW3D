#pragma once
#include "EnemyBuilder.h"

namespace Sample
{
    class ZombieBuilder : public EnemyBuilder
    {
    private:
		//アクション生成
		ActionCreatorPtr		m_ActionCreator;
		//ステート生成
		StateCreatorPtr			m_StateCreator;
		//パラメーター生成
		ParameterCreatorPtr		m_ParameterCreator;
		//AI生成
		CharacterAICreatorPtr	m_AiCreator;
    public:
		ZombieBuilder(const ActionCreatorPtr& actionCreator,
			const StateCreatorPtr& stateCreator,
			const ParameterCreatorPtr& parameterCreator,
			const CharacterAICreatorPtr& aiCreator);

        EnemyPtr Create(const EnemyBuildParameter& param) override;
    };
}


