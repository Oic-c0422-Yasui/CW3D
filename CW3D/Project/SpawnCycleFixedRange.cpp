#include "SpawnCycleFixedRange.h"
#include "Timer.h"


Spawner::SpawnCycleFixedRange::SpawnCycleFixedRange(int interval,CHARA_TYPE type)
	: m_Interval(interval)
	, m_CurrentTime(0.0f)
	, m_Type(type)
{
}

bool Spawner::SpawnCycleFixedRange::Update()
{
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(m_Type);
	if (m_CurrentTime > m_Interval)
	{
		m_CurrentTime -= m_Interval;
		return true;
	}
	return false;
}
