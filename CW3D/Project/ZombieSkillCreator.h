#pragma once
#include "ISkillCreator.h"

namespace ActionGame
{
	class ZombieSkillCreator : public ISkillCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor) override;
	};

}



