#pragma once
#include "ISkillCreator.h"

namespace ActionGame
{
	class MutantSkillCreator : public ISkillCreator
	{
	public:
		/**
		 * @brief		ê∂ê¨
		 */
		bool Create(const ActorPtr& actor) override;
	};

}


