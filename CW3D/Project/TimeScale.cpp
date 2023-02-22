#include "TimeScale.h"

ActionGame::TimeScale::TimeScale()
	: time_(1.0f)
	, m_ChangeFlg(false)
	, m_ChangeTime(0.0f)
	, m_Count(0)
	, currentTime_(0.0f)
	, m_AnimDataArray()
{
}

void ActionGame::TimeScale::Update()
{
	if (!m_ChangeFlg)
	{
		return;
	}
	if (m_ChangeTime > currentTime_)
	{
		currentTime_ += CUtilities::GetFrameSecond();
	}
	else
	{
		m_ChangeFlg = false;
	}
	time_ = MyUtil::InterpolationAnim(currentTime_, m_AnimDataArray);
}

void ActionGame::TimeScale::SetScale(float scale, float changeTime, MyUtil::EASING_TYPE easeType) noexcept
{
	m_Count = 2;
	MyUtil::ANIM_DATA_ARRAY anim(
		{
			{0, time_, easeType},
			{changeTime, scale, easeType}
		}
	);

	m_AnimDataArray = anim;
	currentTime_ = 0.0f;
	m_ChangeTime = changeTime;
	m_ChangeFlg = true;
}


void ActionGame::TimeScale::SetScale(const MyUtil::ANIM_DATA_ARRAY& anim)
{
	m_AnimDataArray = anim;
	m_ChangeTime = m_AnimDataArray.back().Time;
	currentTime_ = 0.0f;
	m_ChangeFlg = true;
}

void ActionGame::TimeScale::Reset() noexcept
{
	time_ = 1.0f;
	currentTime_ = 0.0f;
	m_ChangeTime = 0.0f;
	m_ChangeFlg = false;
}
