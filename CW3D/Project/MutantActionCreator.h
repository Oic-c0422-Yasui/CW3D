#pragma once

#include "IActionCreator.h"


namespace ActionGame
{
	/**
	 * @brief		ミュータントアクション生成クラス
	 */
    class MutantActionCreator :  public IActionCreator
    {
		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr & actor) override;
    };
}


