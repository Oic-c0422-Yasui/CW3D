#include "Skill.h"


ActionGame::Skill::Skill()

	: m_Key()
	, m_InputKey()
	, m_State(nullptr)
	, m_FlyState(nullptr)
	, m_CanUseFlg(false)
	, m_CT(0.0f)
	, m_StartFlg(false)
	, m_SkillData(std::make_shared<SkillData>())

{
}

void ActionGame::Skill::Create(const std::string& name, const std::string& inputKey, const std::string& texName, char* state, char* flyState)
{
	m_Key = name;
	m_InputKey = inputKey;
	m_TexName = texName;
	m_State = state;
	m_FlyState = flyState;
	m_CanUseFlg = true;
	m_StartFlg = false;
}

void ActionGame::Skill::Reset()
{
	m_StartFlg = false;
	m_CanUseFlg = true;
	m_CT = 0.0f;
}

void ActionGame::Skill::Start()
{
	m_CT = m_SkillData->MaxCT.Get();
	m_CanUseFlg = false;
	m_StartFlg = true;
}

void ActionGame::Skill::Update()
{
	if (!m_StartFlg)
	{
		return;
	}
	AddTimerAndResetFlg();
}

void ActionGame::Skill::AddTimerAndResetFlg()
{
	if (m_CT > 0.0f)
	{
		m_CT -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
	else
	{
		m_StartFlg = false;
		m_CanUseFlg = true;
	}
}

void ActionGame::Skill::AddTimer()
{
	if (m_CT > 0.0f)
	{
		m_CT -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
}

void ActionGame::Skill::ResetFlg()

{
	if (m_CT <= 0.0f)
	{
		m_StartFlg = false;
		m_CanUseFlg = true;
	}
}
