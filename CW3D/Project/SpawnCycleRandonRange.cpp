#include "SpawnCycleRandonRange.h"
#include "TimeScaleController.h"
#include "GameDefine.h"

Spawner::SpawnCycleRandomRange::SpawnCycleRandomRange(int min, int max)
	: m_IntervalMin(min)
	, m_IntervalMax(max)
	, m_CurrentInterval(GameFrameTime * CUtilities::Random(min, max))
	, m_CurrentTime(0.0f)
{
}

bool Spawner::SpawnCycleRandomRange::Update()
{
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	if (m_CurrentTime > m_CurrentInterval)
	{
		m_CurrentTime -= m_CurrentInterval;
		m_CurrentInterval = GameFrameTime * CUtilities::Random(m_IntervalMin, m_IntervalMax);
		return true;
	}
	return false;
}
