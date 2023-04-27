#pragma once

#include	"IActionCreator.h"



namespace ActionGame {
	/**
	 * @brief		アクション生成インターフェイス
	 */
	class PlayerActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr& actor) override;
	};
}