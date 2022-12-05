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

	for (auto& enemy : *m_Enemys)
	{
		enemy->Update();

		//�G���\������Ă��鎞�A�������͔�\����������ł��Ȃ����A�G�̐����J�E���g
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
