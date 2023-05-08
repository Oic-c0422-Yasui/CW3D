#pragma once

#include "ISkillCreator.h"

namespace ActionGame {

	/**
	 * @brief		スキル生成
	 */
	class PlayerSkillCreator : public ISkillCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr& actor) override; 
	};


}