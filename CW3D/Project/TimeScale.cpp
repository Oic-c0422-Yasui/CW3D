#include "TimeScale.h"

ActionGame::TimeScale::TimeScale()
	: m_Time(1.0f)
	, m_ChangeFlg(false)
	, m_ChangeTime(0.0f)
	, m_Count(0)
	, m_CurrentTime(0.0f)
	, m_AnimDataArray()
{
}

void ActionGame::TimeScale::Update()
{
	if (!m_ChangeFlg)
	{
		return;
	}
	if (m_ChangeTime > m_CurrentTime)
	{
		m_CurrentTime += CUtilities::GetFrameSecond();
	}
	else
	{
		m_ChangeFlg = false;
	}
	m_Time = MyUtilities::InterpolationAnim(m_CurrentTime, m_AnimDataArray);
}

void ActionGame::TimeScale::SetScale(float scale, float changeTime, MyUtilities::EASING_TYPE easeType) noexcept
{
	m_Count = 2;
	MyUtilities::ANIM_DATA_ARRAY anim(
		{
			{0, m_Time, easeType},
			{changeTime, scale, easeType}
		}
	);

	m_AnimDataArray = anim;
	m_CurrentTime = 0.0f;
	m_ChangeTime = changeTime;
	m_ChangeFlg = true;
}


void ActionGame::TimeScale::SetScale(const MyUtilities::ANIM_DATA_ARRAY& anim)
{
	m_AnimDataArray = anim;
	m_ChangeTime = m_AnimDataArray.back().Time;
	m_CurrentTime = 0.0f;
	m_ChangeFlg = true;
}

void ActionGame::TimeScale::Reset() noexcept
{
	m_Time = 1.0f;
	m_CurrentTime = 0.0f;
	m_ChangeTime = 0.0f;
	m_ChangeFlg = false;
}
