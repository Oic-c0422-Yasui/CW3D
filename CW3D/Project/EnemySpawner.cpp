#include	"EnemySpawner.h"

Spawner::CEnemySpawner::CEnemySpawner(const SpawnConditionArray& conditions, SpawnCyclePtr cycle)
	: conditions_(conditions)
	, cycle_(cycle)

{
}
void Spawner::CEnemySpawner::Update(const ActionGame::EnemyPtr& enemy)
{
	//‚Ç‚ê‚©ˆê‚Â‚Å‚àğŒ‚ğ–‚½‚³‚È‚¢‚È‚çÀs‚µ‚È‚¢
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
	//oŒ»ğŒ‚ª–³‚¢ê‡‚Í—LŒø‰»
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
