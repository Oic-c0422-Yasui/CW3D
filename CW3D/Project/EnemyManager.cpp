#include "EnemyManager.h"

ActionGame::EnemyManager::EnemyManager()
	: m_Enemys(std::make_shared<EnemyArray>())
{
}

ActionGame::EnemyManager::~EnemyManager()
{
}


void ActionGame::EnemyManager::Initialize()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->Initialize();
	}
}

void ActionGame::EnemyManager::Update()
{
	size_t enemyCount = 0;
	size_t enemyShowCount = 0;
	size_t bossCount = 0;

	for (auto& enemy : *m_Enemys)
	{
		enemy->Update();

		//敵が表示されている時、もしくは非表示だが死んでいない時、敵の数をカウント
		if (enemy->IsShow())
		{
			enemyCount++;
			enemyShowCount++;

			if (enemy->IsBoss())
			{
				bossCount++;
			}

			continue;
		}
		else if ((!enemy->IsDead() && !enemy->IsShow()))
		{
			enemyCount++;
			if (enemy->IsBoss())
			{
				bossCount++;
			}

			continue;
		}
	}

	if (m_EnemyCount != enemyCount)
	{
		m_EnemyCount.Set(enemyCount);
	}
	if (m_EnemyShowCount != enemyShowCount)
	{
		m_EnemyShowCount.Set(enemyShowCount);
	}
	if (m_BossCount != bossCount)
	{
		m_BossCount.Set(bossCount);
	}
}

void ActionGame::EnemyManager::Render()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->Render();
	}
}

void ActionGame::EnemyManager::RenderDebug()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->RenderDebug();
	}
}

void ActionGame::EnemyManager::Release()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->Release();
	}
	m_Enemys->clear();
	m_Enemys.reset();
}

void ActionGame::EnemyManager::AddEnemy(const EnemyPtr& enemy)
{
	m_Enemys->push_back(enemy);
	m_EnemyCount = m_Enemys->size();
	m_EnemyMaxCount = m_Enemys->size();
	if (enemy->IsBoss())
	{
		m_BossMaxCount ++;
		m_BossCount = m_BossMaxCount;
	}
}
