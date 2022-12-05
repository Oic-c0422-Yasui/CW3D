#pragma once

#include	"ICharacterAI.h"

namespace ActionGame
{
	/**
	 * @brief		AI�����C���^�[�t�F�C�X
	 */
	class __declspec(novtable) ICharacterAICreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ICharacterAICreator() = default;

		/**
		 * @brief		�R���X�g���N�^
		 */
		virtual CharacterAIPtr Create(const ActorPtr& actor, const StateMachinePtr& machine,
			const StateInputPtr& input) = 0;
	};
	//�|�C���^�u������
	using CharacterAICreatorPtr = std::shared_ptr<ICharacterAICreator>;
}