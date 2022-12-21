#include	"EnemySpawner.h"

Spawner::EnemySpawner::EnemySpawner(const SpawnConditionArray& conditions, SpawnCyclePtr cycle)
	: m_Conditions(conditions)
	, m_Cycle(cycle)

{
}
void Spawner::EnemySpawner::Update(const ActionGame::EnemyPtr& enemy)
{
	//‚Ç‚ê‚©ˆê‚Â‚Å‚àðŒ‚ð–ž‚½‚³‚È‚¢‚È‚çŽÀs‚µ‚È‚¢
	if (!IsValid())
	{
		return;
	}
	if(m_Cycle->Update())
	{
		if (!enemy->IsShow() && !enemy->IsDead())
		{
			enemy->SetShow(true);
		}
	}
}


void Spawner::EnemySpawner::Reset()
{
	m_Cycle->Reset();
}

bool Spawner::EnemySpawner::IsValid() const
{
	if (m_Conditions.size() <= 0)
	{
		return true;
	}
	for (auto& condition : m_Conditions)
	{
		if (!condition->IsValid())
		{
			return false;
		}
	}
	return true;
}
