#pragma once
#include "Enemy.h"
#include "EnemyBuildParameter.h"

namespace Sample
{
	class EnemyBuilder
	{
	protected:
		//�A�N�V��������
		ActionCreatorPtr		m_ActionCreator;
		//�X�e�[�g����
		StateCreatorPtr			m_StateCreator;
		//�p�����[�^�[����
		ParameterCreatorPtr		m_ParameterCreator;
		//AI����
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


