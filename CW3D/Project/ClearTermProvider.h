#pragma once
#include "GameDefine.h"
#include "Enemy.h"

namespace Sample
{
	class ClearTermProvider
	{
	private:
		float m_ClearTime;
		std::vector<EnemyPtr> m_pEnemys;
	public:
		//TODO:ボスを追加する
		ClearTermProvider(std::vector<EnemyPtr> enemys, float time):
			m_ClearTime(time),
			m_pEnemys(enemys)
		{
			
		}
		~ClearTermProvider() {}

		/**
		 * @brief		クリア時間取得
		 */
		float GetTime() const noexcept 
		{
			return m_ClearTime;
		}

		/**
		 * @brief		敵の数取得
		 */
		int GetEnemyCount() noexcept
		{
			int count = 0;
			for (auto& enemy : m_pEnemys)
			{
				if (enemy->IsShow())
				{
					count++;
				}
			}
			return count;
		}

		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}