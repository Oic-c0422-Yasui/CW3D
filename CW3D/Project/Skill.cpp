#include "Skill.h"


ActionGame::CSkill::CSkill()

	: skillName_()
	, inputKey_()
	, stateName_(nullptr)
	, flyStateName_(nullptr)
	, canUse_(false)
	, CT_(0.0f)
	, isStart_(false)
	, skillData_(std::make_shared<SkillData>())

{
}

void ActionGame::CSkill::Create(const std::string& name, const std::string& inputKey, const std::string& texName, char* state, char* flyState)
{
	skillName_ = name;
	inputKey_ = inputKey;
	texureName_ = texName;
	stateName_ = state;
	flyStateName_ = flyState;
	canUse_ = true;
	isStart_ = false;
}

void ActionGame::CSkill::Reset()
{
	isStart_ = false;
	canUse_ = true;
	CT_ = 0.0f;
}

void ActionGame::CSkill::Start()
{
	CT_ = skillData_->MaxCT.Get();
	canUse_ = false;
	isStart_ = true;
}

void ActionGame::CSkill::Update()
{
	if (!isStart_)
	{
		return;
	}
	AddTimerAndResetFlg();
}

void ActionGame::CSkill::AddTimerAndResetFlg()
{
	if (CT_ > 0.0f)
	{
		CT_ -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
	else
	{
		isStart_ = false;
		canUse_ = true;
	}
}

void ActionGame::CSkill::AddTimer()
{
	if (CT_ > 0.0f)
	{
		CT_ -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
}

void ActionGame::CSkill::ResetFlg()
{
	if (CT_ <= 0.0f)
	{
		isStart_ = false;
		canUse_ = true;
	}
}
