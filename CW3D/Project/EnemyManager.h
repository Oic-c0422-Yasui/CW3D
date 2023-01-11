#pragma once
#include "Enemy.h"

namespace ActionGame
{
	class EnemyManager
	{
	private:
		EnemyArrayPtr m_Enemys;
		ActionGame::ReactiveParameter<size_t> m_EnemyCount;
		ActionGame::ReactiveParameter<size_t> m_BossCount;
		ActionGame::ReactiveParameter<size_t> m_EnemyShowCount;
		size_t m_EnemyMaxCount;
		size_t m_BossMaxCount;
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
			return m_EnemyCount;
		}
		size_t GetEnemyMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}
		size_t GetEnemyShowCount() const noexcept
		{
			return m_EnemyShowCount;
		}
		size_t GetBossCount() const noexcept
		{
			return m_BossCount;
		}
		size_t GetBossMaxCount() const noexcept
		{
			return m_BossMaxCount;
		}


		ActionGame::IObservable<size_t>& GetEnemyCountSubject()
		{
			return m_EnemyCount;
		}
		ActionGame::IObservable<size_t>& GetEnemyShowCountSubject()
		{
			return m_EnemyShowCount;
		}
		ActionGame::IObservable<size_t>& GetBossCountSubject()
		{
			return m_BossCount;
		}

		const EnemyPtr& GetEnemy(size_t num)
		{
			assert(m_Enemys->at(num));
			return m_Enemys->at(num);
		}

		void AddEnemy(const EnemyPtr& enemy);

		void ClearEnemyArray()
		{
			m_Enemys->clear();
			m_EnemyCount.Set(0);
			m_EnemyMaxCount = 0;
		}
	};
}

