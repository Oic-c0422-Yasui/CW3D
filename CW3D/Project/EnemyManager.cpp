#include "EnemyManager.h"

Sample::EnemyManager::EnemyManager()
	: m_Enemys(std::make_shared<EnemyArray>())
{
}

Sample::EnemyManager::~EnemyManager()
{
}


void Sample::EnemyManager::Initialize()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->Initialize();
	}
}

void Sample::EnemyManager::Update()
{
	size_t enemyCount = 0;

	for (auto& enemy : *m_Enemys)
	{
		enemy->Update();

		//敵が表示されている時、もしくは非表示だが死んでいない時、敵の数をカウント
		if (enemy->IsShow())
		{
			enemyCount++;
			continue;
		}
		else if ((!enemy->IsDead() && !enemy->IsShow()))
		{
			enemyCount++;
		}
	}

	if (m_EnemyCount != enemyCount)
	{
		m_EnemyCount.Set(enemyCount);
	}
}

void Sample::EnemyManager::Render()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->Render();
	}
}

void Sample::EnemyManager::RenderDebug()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->RenderDebug();
	}
}

void Sample::EnemyManager::Release()
{
	for (auto& enemy : *m_Enemys)
	{
		enemy->Release();
	}
	m_Enemys->clear();
	m_Enemys.reset();
}
