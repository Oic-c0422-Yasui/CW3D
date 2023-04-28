#pragma once
#include "ICharacterAICreator.h"


namespace ActionGame
{
    class MutantAICreator : public ICharacterAICreator
    {
	public:

		/**
		 * @brief		����
		 */
		CharacterAIPtr Create(const ActorPtr & actor,
			const StateMachinePtr & machine,
			const Input::StateInputPtr & input) override;
    };
}


