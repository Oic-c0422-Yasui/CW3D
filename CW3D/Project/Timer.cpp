#include "Timer.h"

ActionGame::CTimer::CTimer()
	: currentTime_(0.0f)
	, m_TargetTime(0.0f)
	, m_AchieveFlg(false)
	, isStop_(false)
{
}

ActionGame::CTimer::~CTimer()
{
}

void ActionGame::CTimer::Start()
{
	currentTime_ = 0.0f;
	m_TargetTime = 0.0f;
	m_AchieveFlg = false;
	isStop_ = false;
}

void ActionGame::CTimer::Start(float targetTime)
{
	Start();
	m_TargetTime = targetTime;
}

void ActionGame::CTimer::Stop()
{
	isStop_ = true;
}

void ActionGame::CTimer::Update()
{
	if (isStop_)
	{
		return;
	}
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	if (currentTime_ >= m_TargetTime)
	{
		if (!m_AchieveFlg)
		{
			m_AchieveFlg = true;
		}
	}
}

void ActionGame::CTimer::Update(CHARA_TYPE timeScaleType)
{
	if (isStop_)
	{
		return;
	}
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(timeScaleType);
	if (currentTime_ >= m_TargetTime)
	{
		if (!m_AchieveFlg)
		{
			m_AchieveFlg = true;
		}
	}
}
