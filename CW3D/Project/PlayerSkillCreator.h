#pragma once

#include "ISkillCreator.h"

namespace ActionGame {

	/**
	 * @brief		ÉXÉLÉãê∂ê¨
	 */
	class PlayerSkillCreator : public ISkillCreator
	{
	public:
		/**
		 * @brief		ê∂ê¨
		 */
		bool Create(const ActorPtr& actor) override; 
	};


}