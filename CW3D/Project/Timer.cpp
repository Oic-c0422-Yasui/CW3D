#include "Timer.h"

Sample::CTimer::CTimer()
	: m_CurrentTime(0.0f)
	, m_TargetTime(0.0f)
	, m_AchieveFlg(false)
	, m_StopFlg(false)
{
}

Sample::CTimer::~CTimer()
{
}

void Sample::CTimer::Start()
{
	m_CurrentTime = 0.0f;
	m_TargetTime = 0.0f;
	m_AchieveFlg = false;
	m_StopFlg = false;
}

void Sample::CTimer::Start(float targetTime)
{
	Start();
	m_TargetTime = targetTime;
}

void Sample::CTimer::Stop()
{
	m_StopFlg = true;
}

void Sample::CTimer::Update()
{
	if (m_StopFlg)
	{
		return;
	}
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	if (m_CurrentTime >= m_TargetTime)
	{
		if (!m_AchieveFlg)
		{
			m_AchieveFlg = true;
		}
	}
}

void Sample::CTimer::Update(CHARACTER_TYPE timeScaleType)
{
	if (m_StopFlg)
	{
		return;
	}
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(timeScaleType);
	if (m_CurrentTime >= m_TargetTime)
	{
		if (!m_AchieveFlg)
		{
			m_AchieveFlg = true;
		}
	}
}
