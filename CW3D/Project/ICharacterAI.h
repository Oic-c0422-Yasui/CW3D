#pragma once

#include	"IStateAI.h"

namespace ActionGame
{
	/**
	 * @brief		AI�����C���^�[�t�F�C�X
	 */
	class __declspec(novtable) ICharacterAI
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ICharacterAI() = default;

		/**
		 * @brief		�X�V
		 */
		virtual void Update() = 0;
	};
	using CharacterAIPtr = std::shared_ptr<ICharacterAI>;
}

