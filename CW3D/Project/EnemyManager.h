#pragma once
#include "Enemy.h"

namespace ActionGame
{
	class EnemyManager
	{
	private:
		EnemyArrayPtr enemyArray_;
		ActionGame::CReactiveParameter<size_t> enemyCount_;
		ActionGame::CReactiveParameter<size_t> bossCount_;
		ActionGame::CReactiveParameter<size_t> showEnemyCount_;
		size_t enemyMaxCount_;
		size_t bossMaxCount_;
	public:
		EnemyManager();
		~EnemyManager();

		void Initialize();
		void Update();
		void Render();
		void RenderDebug();
		void Release();

		
		size_t GetEnemyCount() const noexcept
		{
			return enemyCount_;
		}
		size_t GetEnemyMaxCount() const noexcept
		{
			return enemyMaxCount_;
		}
		size_t GetShowEnemyCount() const noexcept
		{
			return showEnemyCount_;
		}
		size_t GetBossCount() const noexcept
		{
			return bossCount_;
		}
		size_t GetBossMaxCount() const noexcept
		{
			return bossMaxCount_;
		}


		ActionGame::IObservable<size_t>& GetEnemyCountSubject()
		{
			return enemyCount_;
		}
		ActionGame::IObservable<size_t>& GetEnemyShowCountSubject()
		{
			return showEnemyCount_;
		}
		ActionGame::IObservable<size_t>& GetBossCountSubject()
		{
			return bossCount_;
		}

		const EnemyPtr& GetEnemy(size_t num)
		{
			assert(enemyArray_->at(num));
			return enemyArray_->at(num);
		}

		void AddEnemy(const EnemyPtr& enemy);

		void ClearEnemyArray()
		{
			enemyArray_->clear();
			enemyCount_.Set(0);
			enemyMaxCount_ = 0;
		}
	};
}

