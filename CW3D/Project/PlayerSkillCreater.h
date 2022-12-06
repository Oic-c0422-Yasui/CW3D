#pragma once
#include	"GameDefine.h"
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
		 * @brief		�f�X�g���N�^
		 */
		virtual ~PlayerSkillCreator() = default;

		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor); 
	};


}