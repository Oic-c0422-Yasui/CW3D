#pragma once
#include	"GameDefine.h"
#include	"AdditionalSkill.h"
#include	"UltimateSkill.h"
#include	"IActor.h"




namespace ActionGame {

	/**
	 * @brief		スキル生成
	 */
	class PlayerSkillCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~PlayerSkillCreator() = default;

		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr& actor); 
	};


}