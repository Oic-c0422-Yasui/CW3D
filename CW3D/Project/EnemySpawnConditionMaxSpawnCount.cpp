#include "EnemySpawnConditionCountLimit.h"

Spawner::EnemySpawnConditionCountLimit::EnemySpawnConditionCountLimit(size_t maxCount)
	: m_MaxCount(maxCount)
	, count_(0)
{
}

bool Spawner::EnemySpawnConditionCountLimit::IsValid() const noexcept
{
	return count_ < m_MaxCount;
}
