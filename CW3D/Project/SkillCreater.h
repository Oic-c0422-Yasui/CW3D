#pragma once
#include "SkillManager.h"
#include "GameDefine.h"
#include "SkillData.h"

class CSkillCreater
{
private:
	

public:


	static bool Create()
	{
		Sample::SKillPtr skill;
		skill = SkillManagerInstance.Create(SKILL_KEY_1, INPUT_KEY_SKILL1, STATE_KEY_SKILL1_1, STATE_KEY_SKILL1_1);
		skill->SetCT(5.0f);

		skill = SkillManagerInstance.Create(SKILL_KEY_2, INPUT_KEY_SKILL2, STATE_KEY_SKILL2_1, STATE_KEY_JUMPSKILL2_1);
		skill->SetCT(3.0f);

		skill = SkillManagerInstance.Create(SKILL_KEY_3, INPUT_KEY_SKILL3, STATE_KEY_SKILL3_1, STATE_KEY_JUMPSKILL3_1);
		skill->SetCT(5.0f);
		return true;
	}

};