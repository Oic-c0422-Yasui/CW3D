#include "EnemyManager.h"

ActionGame::EnemyManager::EnemyManager()
	: enemyArray_(std::make_shared<EnemyArray>())
{
}

ActionGame::EnemyManager::~EnemyManager()
{
}


void ActionGame::EnemyManager::Initialize()
{
	for (auto& enemy : *enemyArray_)
	{
		enemy->Initialize();
	}
}

void ActionGame::EnemyManager::Update()
{
	size_t enemyCount = 0;
	size_t enemyShowCount = 0;
	size_t bossCount = 0;

	for (auto& enemy : *enemyArray_)
	{
		enemy->Update();

		//�G���\������Ă��鎞�A�������͔�\����������ł��Ȃ����A�G�̐����J�E���g
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

	//�J�E���g�����l���O�̒l�ƕς���Ă���Βl�𔽉f
	if (enemyCount_ != enemyCount)
	{
		enemyCount_.Set(enemyCount);
	}
	if (showEnemyCount_ != enemyShowCount)
	{
		showEnemyCount_.Set(enemyShowCount);
	}
	if (bossCount_ != bossCount)
	{
		bossCount_.Set(bossCount);
	}
}

void ActionGame::EnemyManager::Render()
{
	for (auto& enemy : *enemyArray_)
	{
		enemy->Render();
	}
}

void ActionGame::EnemyManager::RenderDebug()
{
	for (auto& enemy : *enemyArray_)
	{
		enemy->RenderDebug();
	}
}

void ActionGame::EnemyManager::Release()
{
	for (auto& enemy : *enemyArray_)
	{
		enemy->Release();
	}
	enemyArray_->clear();
	enemyArray_.reset();
}

void ActionGame::EnemyManager::AddEnemy(const EnemyPtr& enemy)
{
	enemyArray_->push_back(enemy);
	enemyCount_ = enemyArray_->size();
	enemyMaxCount_ = enemyArray_->size();
	if (enemy->IsBoss())
	{
		bossMaxCount_ ++;
		bossCount_ = bossMaxCount_;
	}
}
