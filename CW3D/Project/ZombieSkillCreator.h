#pragma once
#include "ISkillCreator.h"

namespace ActionGame
{
	class ZombieSkillCreator : public ISkillCreator
	{
	public:
		/**
		 * @brief		ê∂ê¨
		 */
		bool Create(const ActorPtr& actor) override;
	};

}



