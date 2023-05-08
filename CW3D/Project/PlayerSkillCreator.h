#pragma once

#include "ISkillCreator.h"

namespace ActionGame {

	/**
	 * @brief		�X�L������
	 */
	class PlayerSkillCreator : public ISkillCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor) override; 
	};


}