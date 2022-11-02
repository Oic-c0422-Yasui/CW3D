#pragma once
#include "EnemyBuilder.h"

namespace Sample
{
    class ZombieBuilder : public EnemyBuilder
    {
    private:
		//�A�N�V��������
		ActionCreatorPtr		m_ActionCreator;
		//�X�e�[�g����
		StateCreatorPtr			m_StateCreator;
		//�p�����[�^�[����
		ParameterCreatorPtr		m_ParameterCreator;
		//AI����
		CharacterAICreatorPtr	m_AiCreator;
    public:
		ZombieBuilder(const ActionCreatorPtr& actionCreator,
			const StateCreatorPtr& stateCreator,
			const ParameterCreatorPtr& parameterCreator,
			const CharacterAICreatorPtr& aiCreator);

        EnemyPtr Create(const EnemyBuildParameter& param) override;
    };
}


