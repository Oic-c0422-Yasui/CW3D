#pragma once
#include "SkillManager.h"
#include "GameDefine.h"

class CSkillCreater
{
private:


public:


	static bool Create()
	{
		SkillManagerInstance.Create(SKILL_KEY_1, INPUT_KEY_SKILL1, STATE_KEY_SKILL1_1, STATE_KEY_SKILL1_1);
		return true;
	}

};