#pragma once
#include "ISkillCreator.h"

namespace ActionGame
{
	class MutantSkillCreator : public ISkillCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor) override;
	};

}


