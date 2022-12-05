#include	"EnemySpawner.h"
#include	"ActorObjectManager.h"

Spawner::EnemySpawner::EnemySpawner(const SpawnConditionArray& conditions, SpawnCyclePtr cycle, EnemySpawnParameter param)
	: m_Conditions(conditions)
	, m_Cycle(cycle)
	, m_EnemyParam(param)
{
}
void Spawner::EnemySpawner::Update(ActionGame::EnemyManager& manager)
{
	//どれか一つでも条件を満たさないなら実行しない
	if (!IsValid())
	{
		return;
	}
	while (m_Cycle->Update())
	{
		manager.AddEnemy(Spawn(m_EnemyParam.GetParameter()));
		m_EnemyParam.Next();
	}
}

ActionGame::EnemyPtr Spawner::EnemySpawner::Spawn(const ActionGame::EnemyBuildParameterPtr& param)
{
	ActionGame::EnemyBuilderDictionary dictionary;
	 //ビルダー取得
	auto builder = dictionary.Get(param->GetParam().m_Type);
	//敵生成
	auto obj = builder->Create(param);
	//アクターマネージャーに登録
	ActorObjectManagerInstance.Add(obj);

	return obj;
}

void Spawner::EnemySpawner::Reset()
{
	m_Cycle->Reset();
}

bool Spawner::EnemySpawner::IsValid() const
{
	for (auto& condition : m_Conditions)
	{
		if (!condition->IsValid())
		{
			return false;
		}
	}
	return true;
}
