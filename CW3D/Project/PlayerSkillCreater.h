#pragma once

#include	"AdditionalSkill.h"
#include	"UltimateSkill.h"
#include	"IActor.h"




namespace ActionGame {

	/**
	 * @brief		�X�L������
	 */
	class PlayerSkillCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor); 
	};


}