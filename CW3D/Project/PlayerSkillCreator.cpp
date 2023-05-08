#include "PlayerSkillCreator.h"
#include "GameDefine.h"
#include	"AdditionalSkill.h"
#include	"UltimateSkill.h"

bool ActionGame::PlayerSkillCreator::Create(const ActorPtr& actor)
{

	ActionGame::SKillPtr skill;


	skill = actor->GetSkillController()->Create(SKILL_KEY_1, INPUT_KEY_SKILL2, "Skill1", STATE_KEY_BEAM_SKILL, STATE_KEY_JUMP_BEAM_SKILL);
	skill->SetSkillData(180, 10);

	skill = actor->GetSkillController()->Create(SKILL_KEY_2, INPUT_KEY_SKILL3, "Skill2", STATE_KEY_STORM_SKILL, STATE_KEY_JUMP_STORM_SKILL);
	skill->SetSkillData(125, 15);

	skill = actor->GetSkillController()->Create(SKILL_KEY_5, INPUT_KEY_SKILL5, "Skill5", STATE_KEY_FLYHIGH_SKILL, STATE_KEY_FLYHIGH_SKILL);
	skill->SetSkillData(700, 6);
	skill = actor->GetSkillController()->Create(SKILL_KEY_6, INPUT_KEY_SKILL6, "Skill6", STATE_KEY_IMPACT_SKILL, STATE_KEY_IMPACT_SKILL);
	skill->SetSkillData(1200, 12);


	ActionGame::SKillPtr ult = std::make_shared<ActionGame::UltimateSkill>(actor);
	skill = actor->GetSkillController()->Create(SKILL_KEY_3, INPUT_KEY_SKILL1, "Skill4", STATE_KEY_SHOCKWAVE_SKILL, STATE_KEY_SHOCKWAVE_SKILL, ult);

	auto ultData = std::make_shared<UltimateSkillData>(650, 20, 75.0f);
	skill->SetSkillData(ultData);

	ult = std::make_shared<ActionGame::UltimateSkill>(actor);
	skill = actor->GetSkillController()->Create(SKILL_KEY_8, INPUT_KEY_SKILL8, "Skill8", STATE_KEY_FIREFLAME_SKILL, STATE_KEY_FIREFLAME_SKILL, ult);
	ultData = std::make_shared<UltimateSkillData>(4600, 15, 60.0f);
	skill->SetSkillData(ultData);

	skill = actor->GetSkillController()->Create(SKILL_KEY_ESCAPE, INPUT_KEY_ESCAPE, "Escape", STATE_KEY_ESCAPE, STATE_KEY_ESCAPE);
	skill->SetMaxCT(1);

	ActionGame::SKillPtr addSkill = std::make_shared<ActionGame::CAdditionalSkill>();
	skill = actor->GetSkillController()->Create(SKILL_KEY_4, INPUT_KEY_SKILL4, "Skill3", STATE_KEY_DROPKICK_SKILL, STATE_KEY_DROPKICK_SKILL, addSkill);
	auto addData = std::make_shared<AdditionalSkillData>(800, 8, 3.5f, GameFrameTime * 20.0f, 0);
	skill->SetSkillData(addData);
	addSkill = std::make_shared<ActionGame::CAdditionalSkill>();
	skill = actor->GetSkillController()->Create(SKILL_KEY_7, INPUT_KEY_SKILL7, "Skill7", STATE_KEY_CHASE_SKILL, STATE_KEY_CHASE_SKILL, addSkill);
	addData = std::make_shared<AdditionalSkillData>(100, 5, 3.5f, GameFrameTime * 30.0f, 0);
	skill->SetSkillData(addData);

	return true;
}
