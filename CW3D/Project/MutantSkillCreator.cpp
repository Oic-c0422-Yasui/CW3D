#include "MutantSkillCreator.h"


bool ActionGame::MutantSkillCreator::Create(const ActorPtr& actor)
{
	ActionGame::SKillPtr skill;

	skill = actor->GetSkillController()->Create(SKILL_KEY_1, INPUT_KEY_SKILL1, "Skill1", STATE_KEY_SPEAR_ATTACK, STATE_KEY_SPEAR_ATTACK);
	skill->SetSkillData(100, 25);


	return true;
}
