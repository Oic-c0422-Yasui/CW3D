#include	"EnemySpawner.h"

Spawner::CEnemySpawner::CEnemySpawner(const SpawnConditionArray& conditions, SpawnCyclePtr cycle)
	: conditions_(conditions)
	, cycle_(cycle)

{
}
void Spawner::CEnemySpawner::Update(const ActionGame::EnemyPtr& enemy)
{
	//どれか一つでも条件を満たさないなら実行しない
	if (!IsValid())
	{
		return;
	}
	if(cycle_->Update())
	{
		if (!enemy->IsShow() && !enemy->IsDead())
		{
			enemy->SetShow(true);
		}
	}
}


void Spawner::CEnemySpawner::Reset()
{
	cycle_->Reset();
}

bool Spawner::CEnemySpawner::IsValid() const
{
	//出現条件が無い場合は有効化
	if (conditions_.size() <= 0)
	{
		return true;
	}

	for (auto& condition : conditions_)
	{
		if (!condition->IsValid())
		{
			return false;
		}
	}
	return true;
}
