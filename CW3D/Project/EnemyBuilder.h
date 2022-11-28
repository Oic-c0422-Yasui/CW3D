#pragma once
#include "Enemy.h"
#include "EnemyBuildParameter.h"

namespace Sample
{
	class EnemyBuilder
	{
	protected:
		//アクション生成
		ActionCreatorPtr		m_ActionCreator;
		//ステート生成
		StateCreatorPtr			m_StateCreator;
		//パラメーター生成
		ParameterCreatorPtr		m_ParameterCreator;
		//AI生成
		CharacterAICreatorPtr	m_AiCreator;
	public:
		EnemyBuilder(const ActionCreatorPtr& actionCreator,
			const StateCreatorPtr& stateCreator,
			const ParameterCreatorPtr& parameterCreator,
			const CharacterAICreatorPtr& aiCreator)
			: m_ActionCreator(actionCreator)
			, m_StateCreator(stateCreator)
			, m_ParameterCreator(parameterCreator)
			, m_AiCreator(aiCreator)
		{
		}
		virtual ~EnemyBuilder() = default;
		virtual EnemyPtr Create(const EnemyBuildParameterPtr& param) = 0;
	};

	using EnemyBuilderPtr = std::shared_ptr<EnemyBuilder>;

}


