#pragma once
#include "SkillManager.h"
#include "GameDefine.h"

class CSkillCreater
{
private:


public:


	static bool Create()
	{
		SkillManagerInstance.Create("s1", INPUT_KEY_SKILL1, STATE_KEY_SKILL1_1, 10.0f, 5);
		return true;
	}

};