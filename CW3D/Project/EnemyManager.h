#pragma once
#include "Enemy.h"

namespace ActionGame
{
	class EnemyManager
	{
	private:
		EnemyArrayPtr m_Enemys;
		ActionGame::ReactiveParameter<size_t> m_EnemyCount;
		size_t m_EnemyMaxCount;
	public:
		EnemyManager();
		~EnemyManager();

		void Initialize();
		void Update();
		void Render();
		void RenderDebug();
		void Release();

		
		size_t GetMaxEnemyCount() const noexcept
		{
			return m_EnemyMaxCount;
		}

		ActionGame::IObservable<size_t>& GetEnemyCountSubject()
		{
			return m_EnemyCount;
		}
		size_t GetEnemyCount() const noexcept
		{
			return m_EnemyCount;
		}

		const EnemyPtr& GetEnemy(size_t num)
		{
			assert(m_Enemys->at(num));
			return m_Enemys->at(num);
		}

		void AddEnemy(const EnemyPtr& enemy)
		{
			m_Enemys->push_back(enemy);
			m_EnemyCount = m_Enemys->size();
			m_EnemyMaxCount = m_Enemys->size();
		}

		void ClearEnemyArray()
		{
			m_Enemys->clear();
			m_EnemyCount.Set(0);
			m_EnemyMaxCount = 0;
		}
	};
}

