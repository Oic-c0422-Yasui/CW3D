#include "SpawnCycleFixedRange.h"
#include "Timer.h"

Spawner::SpawnCycleFixedRange::SpawnCycleFixedRange(int interval)
	: m_Interval(interval)
	, m_CurrentTime(0.0f)
{
}

bool Spawner::SpawnCycleFixedRange::Update()
{
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	if (m_CurrentTime > m_Interval)
	{
		m_CurrentTime -= m_Interval;
		return true;
	}
	return false;
}
