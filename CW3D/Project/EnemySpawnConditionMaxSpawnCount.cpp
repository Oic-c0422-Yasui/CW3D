#include "EnemySpawnConditionCountLimit.h"

Spawner::EnemySpawnConditionCountLimit::EnemySpawnConditionCountLimit(size_t maxCount)
	: m_MaxCount(maxCount)
	, m_Count(0)
{
}

bool Spawner::EnemySpawnConditionCountLimit::IsValid() const noexcept
{
	return m_Count < m_MaxCount;
}
