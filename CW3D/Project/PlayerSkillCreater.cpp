#include "PlayerSkillCreater.h"


bool ActionGame::PlayerSkillCreator::Create(const ActorPtr& actor)
{

	ActionGame::SKillPtr skill;


	skill = actor->GetSkillController()->Create(SKILL_KEY_1, INPUT_KEY_SKILL2, "Skill1", STATE_KEY_BEAMSKILL, STATE_KEY_JUMPBEAMSKILL);
	skill->SetSkillData(180, 5);

	skill = actor->GetSkillController()->Create(SKILL_KEY_2, INPUT_KEY_SKILL3, "Skill2", STATE_KEY_STORMSKILL, STATE_KEY_JUMPSTORMSKILL);
	skill->SetSkillData(125, 8);


	ActionGame::SKillPtr ult = std::make_shared<ActionGame::CUltimateSkill>(actor);
	skill = actor->GetSkillController()->Create(SKILL_KEY_3, INPUT_KEY_SKILL1, "Skill3", STATE_KEY_SHOCKWAVESKILL, STATE_KEY_SHOCKWAVESKILL, ult);

	UltimateSkillDataPtr ultData = std::make_shared<UltimateSkillData>(550, 8, 75.0f);
	skill->SetSkillData(ultData);

	skill = actor->GetSkillController()->Create(SKILL_KEY_ESCAPE, INPUT_KEY_ESCAPE, "Escape", STATE_KEY_ESCAPE, STATE_KEY_ESCAPE);
	skill->SetMaxCT(1);

	ActionGame::SKillPtr additionalSkill = std::make_shared<ActionGame::CAdditionalSkill>();
	skill = actor->GetSkillController()->Create(SKILL_KEY_DROPKICK, INPUT_KEY_SKILL_DROPKICK, "DropKick", STATE_KEY_DROPKICKSKILL, STATE_KEY_DROPKICKSKILL, additionalSkill);
	AdditionalSkillDataPtr addData = std::make_shared<AdditionalSkillData>(1200, 5, 2.5f, GameFrameTime * 30.0f, 0);
	skill->SetSkillData(addData);

	return true;
}
