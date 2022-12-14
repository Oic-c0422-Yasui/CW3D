#include "AdditionalSkill.h"

ActionGame::AdditionalSkill::AdditionalSkill()

	: Skill()
	, m_AddStartTime(0.0f)
	, m_AddCT(0.0f)
	, m_AddCount(0)
	, m_AddFlg(false)
	, m_DelayAddFlg(false)
{
}

ActionGame::AdditionalSkill::~AdditionalSkill()
{
}

void ActionGame::AdditionalSkill::Start()
{
	if (!m_AddFlg)
	{
		Skill::Start();
		m_AddStartTime = m_AddSkillData->StartTime;
	}
	else
	{
		m_DelayAddFlg = true;
		AddInput();
	}
}

void ActionGame::AdditionalSkill::Reset()
{
	Skill::Reset();
	m_AddStartTime = 0.0f;
	m_AddCT = 0.0f;
	m_AddCount = 0;
	m_AddFlg = false;
	m_DelayAddFlg = false;
}

void ActionGame::AdditionalSkill::Update()
{
	if (!m_StartFlg)
	{
		return;
	}
	if (m_AddStartTime > 0.0f)
	{
		m_AddStartTime -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
		if (m_AddStartTime <= 0.0f)
		{
			if (!m_AddFlg)
			{
				m_AddFlg = true;
				m_AddCT = m_AddSkillData->AddMaxCT.Get();
				m_DelayAddFlg = false;
			}
		}
	}
	else if (m_AddCT > 0.0f)
	{
		m_AddCT -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	if (m_AddCT <= 0.0f)
	{
		m_AddFlg = false;
		Skill::AddTimerAndResetFlg();
	}
}

void ActionGame::AdditionalSkill::SetSkillData(const SkillDataPtr& skill)
{
	Skill::SetSkillData(skill);
	m_AddSkillData = std::dynamic_pointer_cast<AdditionalSkillData>(m_SkillData);
	if (m_AddSkillData == nullptr)
	{
		assert(m_AddSkillData);
	}
}
