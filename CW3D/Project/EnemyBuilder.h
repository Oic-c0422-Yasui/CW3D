#pragma once

#include "EnemyBuildParameter.h"
#include "Enemy.h"

namespace ActionGame
{
	class EnemyBuilder
	{
	protected:
		//�A�N�V��������
		ActionCreatorPtr		actionCreator_;
		//�X�e�[�g����
		StateCreatorPtr			stateCreator_;
		//�p�����[�^�[����
		ParameterCreatorPtr		parameterCreator_;
		//AI����
		CharacterAICreatorPtr	AICreator_;
	public:
		EnemyBuilder(const ActionCreatorPtr& actionCreator,
			const StateCreatorPtr& stateCreator,
			const ParameterCreatorPtr& parameterCreator,
			const CharacterAICreatorPtr& aiCreator)
			: actionCreator_(actionCreator)
			, stateCreator_(stateCreator)
			, parameterCreator_(parameterCreator)
			, AICreator_(aiCreator)
		{
		}
		virtual ~EnemyBuilder() = default;
		virtual EnemyPtr Create(const EnemyBuildParameterPtr& param) = 0;
	};

	using EnemyBuilderPtr = std::shared_ptr<EnemyBuilder>;

}


