#include "SpawnCycleFixedRange.h"
#include "Timer.h"


Spawner::SpawnCycleFixedRange::SpawnCycleFixedRange(int interval,CHARA_TYPE type)
	: m_Interval(interval)
	, currentTime_(0.0f)
	, type_(type)
{
}

bool Spawner::SpawnCycleFixedRange::Update()
{
	currentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(type_);
	if (currentTime_ > m_Interval)
	{
		currentTime_ -= m_Interval;
		return true;
	}
	return false;
}
