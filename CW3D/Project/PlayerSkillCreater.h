#pragma once

#include	"AdditionalSkill.h"
#include	"UltimateSkill.h"
#include	"IActor.h"




namespace ActionGame {

	/**
	 * @brief		ÉXÉLÉãê∂ê¨
	 */
	class PlayerSkillCreator
	{
	public:
		/**
		 * @brief		ê∂ê¨
		 */
		bool Create(const ActorPtr& actor); 
	};


}