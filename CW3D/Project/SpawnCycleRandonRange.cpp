#include "SpawnCycleRandonRange.h"
#include "TimeScaleController.h"
#include "GameDefine.h"

Spawner::SpawnCycleRandomRange::SpawnCycleRandomRange(int min, int max)
	: m_IntervalMin(min)
	, m_IntervalMax(max)
	, m_CurrentInterval(GameFrameTime * CUtilities::Random(min, max))
	, currentTime_(0.0f)
{
}

bool Spawner::SpawnCycleRandomRange::Update()
{
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	if (currentTime_ > m_CurrentInterval)
	{
		currentTime_ -= m_CurrentInterval;
		m_CurrentInterval = GameFrameTime * CUtilities::Random(m_IntervalMin, m_IntervalMax);
		return true;
	}
	return false;
}
