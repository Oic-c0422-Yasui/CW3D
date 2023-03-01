#include "Skill.h"


ActionGame::Skill::Skill()

	: inputKey_()
	, m_InputKey()
	, m_State(nullptr)
	, m_FlyState(nullptr)
	, m_CanUseFlg(false)
	, m_CT(0.0f)
	, isStart_(false)
	, m_SkillData(std::make_shared<SkillData>())

{
}

void ActionGame::Skill::Create(const std::string& name, const std::string& inputKey, const std::string& texName, char* state, char* flyState)
{
	inputKey_ = name;
	m_InputKey = inputKey;
	m_TexName = texName;
	m_State = state;
	m_FlyState = flyState;
	m_CanUseFlg = true;
	isStart_ = false;
}

void ActionGame::Skill::Reset()
{
	isStart_ = false;
	m_CanUseFlg = true;
	m_CT = 0.0f;
}

void ActionGame::Skill::Start()
{
	m_CT = m_SkillData->MaxCT.Get();
	m_CanUseFlg = false;
	isStart_ = true;
}

void ActionGame::Skill::Update()
{
	if (!isStart_)
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
		isStart_ = false;
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
		isStart_ = false;
		m_CanUseFlg = true;
	}
}
