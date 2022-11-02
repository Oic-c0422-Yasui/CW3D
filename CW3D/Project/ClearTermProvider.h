#pragma once
#include "GameDefine.h"
#include "Enemy.h"

namespace Sample
{
	class ClearTermProvider
	{
	private:
		float m_CurrentTime;
		EnemyArrayPtr m_Enemys;
	public:
		//TODO:�{�X��ǉ�����
		ClearTermProvider(const EnemyArrayPtr& enemys):
			m_CurrentTime(0.0f),
			m_Enemys(enemys)
		{
			
		}
		~ClearTermProvider() {}

		/**
		 * @brief		���ݎ��Ԏ擾
		 */
		float GetTime() const noexcept 
		{
			return m_CurrentTime;
		}

		/**
		 * @brief		�G�擾
		 */
		const EnemyArrayPtr& GetEnemy()
		{
			return m_Enemys;
		}

		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}