#include "TimeScale.h"

Sample::TimeScale::TimeScale()
	: m_Time(1.0f)
	, m_ChangeFlg(false)
	, m_ChangeTime(0.0f)
	, m_Count(0)
	, m_AnimData()
{
}

void Sample::TimeScale::Update()
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
	//m_Time = MyUtilities::InterpolationAnim(m_CurrentTime, m_AnimData, m_Count);
}

void Sample::TimeScale::SetScale(float scale, float changeTime, MyUtilities::EASING_TYPE easeType) noexcept
{
	m_Count = 2;
	MyUtilities::ANIM_DATA anim[2] =
	{
		{0, m_Time, easeType},
		{changeTime, scale, easeType}
	};
	m_AnimData[0] = anim[0];
	m_AnimData[1] = anim[1];
	m_CurrentTime = 0.0f;
	m_ChangeTime = changeTime;
	m_ChangeFlg = true;
}

void Sample::TimeScale::SetScale(MyUtilities::ANIM_DATA* anim, size_t count)
{
	memcpy(m_AnimData, anim, sizeof(MyUtilities::ANIM_DATA) * count);
	m_Count = count;
	m_ChangeTime = m_AnimData[count - 1].Time;
	m_CurrentTime = 0.0f;
	m_ChangeFlg = true;
}

void Sample::TimeScale::SetScale(const MyUtilities::ANIM_DATA_ARRAY& anim)
{
	m_AnimDataArray = anim;
	m_ChangeTime = m_AnimDataArray.back().Time;
	m_CurrentTime = 0.0f;
	m_ChangeFlg = true;
}

void Sample::TimeScale::Reset() noexcept
{
	m_Time = 1.0f;
	m_CurrentTime = 0.0f;
	m_ChangeTime = 0.0f;
	m_ChangeFlg = false;
}
