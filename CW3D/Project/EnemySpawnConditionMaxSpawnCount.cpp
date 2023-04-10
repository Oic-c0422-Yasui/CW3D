#include "EnemySpawnConditionCountLimit.h"

Spawner::CEnemySpawnConditionCountLimit::CEnemySpawnConditionCountLimit(size_t maxCount)
	: maxCount_(maxCount)
	, count_(0)
{
}

bool Spawner::CEnemySpawnConditionCountLimit::IsValid() const noexcept
{
	return count_ < maxCount_;
}
