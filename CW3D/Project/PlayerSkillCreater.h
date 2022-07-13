#pragma once
#include "GameDefine.h"
#include "AdditionalSkill.h"
#include "UltimateSkill.h"
#include	"IActor.h"




namespace Sample {

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
		bool Create(const ActorPtr& actor) {

			Sample::SKillPtr skill;

			
			skill = actor->GetSkillController()->Create(SKILL_KEY_1, INPUT_KEY_SKILL2, "Skill1", STATE_KEY_SKILL2_1, STATE_KEY_JUMPSKILL2_1);
			skill->SetSkillData(180, 5);
			
			skill = actor->GetSkillController()->Create(SKILL_KEY_2, INPUT_KEY_SKILL3, "Skill2", STATE_KEY_SKILL3_1, STATE_KEY_JUMPSKILL3_1);
			skill->SetSkillData(125, 8);


			Sample::SKillPtr ult = std::make_shared<Sample::CUltimateSkill>(actor);
			skill = actor->GetSkillController()->Create(SKILL_KEY_3, INPUT_KEY_SKILL1, "Skill3", STATE_KEY_SKILL1_1, STATE_KEY_SKILL1_1, ult);
			
			UltimateSkillDataPtr ultData = std::make_shared<UltimateSkillData>(550, 8, 75.0f);
			skill->SetSkillData(ultData);

			skill = actor->GetSkillController()->Create(SKILL_KEY_ESCAPE, INPUT_KEY_ESCAPE, "Escape", STATE_KEY_ESCAPE, STATE_KEY_ESCAPE);
			skill->SetMaxCT(1);

			Sample::SKillPtr additionalSkill = std::make_shared<Sample::CAdditionalSkill>();
			skill = actor->GetSkillController()->Create(SKILL_KEY_DROPKICK, INPUT_KEY_SKILL_DROPKICK, "DropKick", STATE_KEY_DROPKICKSKILL, STATE_KEY_DROPKICKSKILL, additionalSkill);
			AdditionalSkillDataPtr addData = std::make_shared<AdditionalSkillData>(1200, 5, 2.5f,GameFrameTime * 30.0f, 0);
			skill->SetSkillData(addData);

			return true;
		}
	};


}