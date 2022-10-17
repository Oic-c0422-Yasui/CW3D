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
		//TODO:�{�X��ǉ�����
		ClearTermProvider(std::vector<EnemyPtr> enemys, float time):
			m_ClearTime(time),
			m_pEnemys(enemys)
		{
			
		}
		~ClearTermProvider() {}

		/**
		 * @brief		�N���A���Ԏ擾
		 */
		float GetTime() const noexcept 
		{
			return m_ClearTime;
		}

		/**
		 * @brief		�G�̐��擾
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