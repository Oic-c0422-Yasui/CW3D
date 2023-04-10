#include "PlayerSkillCreater.h"
#include "GameDefine.h"


bool ActionGame::PlayerSkillCreator::Create(const ActorPtr& actor)
{

	ActionGame::SKillPtr skill;


	skill = actor->GetSkillController()->Create(SKILL_KEY_1, INPUT_KEY_SKILL2, "Skill1", STATE_KEY_BEAM_SKILL, STATE_KEY_JUMP_BEAM_SKILL);
	skill->SetSkillData(180, 5);

	skill = actor->GetSkillController()->Create(SKILL_KEY_2, INPUT_KEY_SKILL3, "Skill2", STATE_KEY_STORM_SKILL, STATE_KEY_JUMP_STORM_SKILL);
	skill->SetSkillData(125, 8);


	ActionGame::SKillPtr ult = std::make_shared<ActionGame::UltimateSkill>(actor);
	skill = actor->GetSkillController()->Create(SKILL_KEY_3, INPUT_KEY_SKILL1, "Skill3", STATE_KEY_SHOCKWAVE_SKILL, STATE_KEY_SHOCKWAVE_SKILL, ult);

	UltimateSkillDataPtr ultData = std::make_shared<UltimateSkillData>(550, 8, 75.0f);
	skill->SetSkillData(ultData);

	skill = actor->GetSkillController()->Create(SKILL_KEY_ESCAPE, INPUT_KEY_ESCAPE, "Escape", STATE_KEY_ESCAPE, STATE_KEY_ESCAPE);
	skill->SetMaxCT(1);

	ActionGame::SKillPtr additionalSkill = std::make_shared<ActionGame::CAdditionalSkill>();
	skill = actor->GetSkillController()->Create(SKILL_KEY_4, INPUT_KEY_SKILL4, "DropKick", STATE_KEY_DROPKICK_SKILL, STATE_KEY_DROPKICK_SKILL, additionalSkill);
	AdditionalSkillDataPtr addData = std::make_shared<AdditionalSkillData>(1200, 5, 2.5f, GameFrameTime * 30.0f, 0);
	skill->SetSkillData(addData);

	return true;
}
