#pragma once

#include "IStateCreator.h"


namespace ActionGame
{
	/**
	 * @brief		ミュータントステート生成
	 */
    class MutantStateCreator : public IStateCreator
    {
		/**
		 * @brief		生成
		 */
		bool Create(const StateMachinePtr & stateMachine, 
					const ActorPtr & actor, 
					const Input::InputPtr & input) override;
    };

}


