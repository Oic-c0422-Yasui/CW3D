#pragma once

#include "IActionCreator.h"


namespace ActionGame
{
	/**
	 * @brief		�~���[�^���g�A�N�V���������N���X
	 */
    class MutantActionCreator :  public IActionCreator
    {
		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr & actor) override;
    };
}


