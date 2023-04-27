#pragma once

#include "IStateCreator.h"


namespace ActionGame
{
	/**
	 * @brief		�~���[�^���g�X�e�[�g����
	 */
    class MutantStateCreator : public IStateCreator
    {
		/**
		 * @brief		����
		 */
		bool Create(const StateMachinePtr & stateMachine, 
					const ActorPtr & actor, 
					const Input::InputPtr & input) override;
    };

}


