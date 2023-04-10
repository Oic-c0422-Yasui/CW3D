#include "AdditionalSkill.h"

ActionGame::CAdditionalSkill::CAdditionalSkill()

	: CSkill()
	, addStartTime_(0.0f)
	, addCT_(0.0f)
	, addCount_(0)
	, isAdd_(false)
	, isDelayAdd_(false)
{
}

ActionGame::CAdditionalSkill::~CAdditionalSkill()
{
}

void ActionGame::CAdditionalSkill::Start()
{
	if (!isAdd_)
	{
		CSkill::Start();
		addStartTime_ = addSkillData_->StartTime;
	}
	else
	{
		isDelayAdd_ = true;
		AddInput();
	}
}

void ActionGame::CAdditionalSkill::Reset()
{
	CSkill::Reset();
	addStartTime_ = 0.0f;
	addCT_ = 0.0f;
	addCount_ = 0;
	isAdd_ = false;
	isDelayAdd_ = false;
}

void ActionGame::CAdditionalSkill::Update()
{
	if (!isStart_)
	{
		return;
	}
	if (addStartTime_ > 0.0f)
	{
		addStartTime_ -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
		if (addStartTime_ <= 0.0f)
		{
			if (!isAdd_)
			{
				isAdd_ = true;
				addCT_ = addSkillData_->AddMaxCT.Get();
				isDelayAdd_ = false;
			}
		}
	}
	else if (addCT_ > 0.0f)
	{
		addCT_ -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	if (addCT_ <= 0.0f)
	{
		isAdd_ = false;
		CSkill::AddTimerAndResetFlg();
	}
}

void ActionGame::CAdditionalSkill::SetSkillData(const SkillDataPtr& skill)
{
	CSkill::SetSkillData(skill);
	addSkillData_ = std::dynamic_pointer_cast<AdditionalSkillData>(skillData_);
	if (addSkillData_ == nullptr)
	{
		assert(addSkillData_);
	}
}
