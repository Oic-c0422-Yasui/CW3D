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
		//TODO:ボスを追加する
		ClearTermProvider(const EnemyArrayPtr& enemys):
			m_CurrentTime(0.0f),
			m_Enemys(enemys)
		{
			
		}
		~ClearTermProvider() {}

		/**
		 * @brief		現在時間取得
		 */
		float GetTime() const noexcept 
		{
			return m_CurrentTime;
		}

		/**
		 * @brief		敵取得
		 */
		const EnemyArrayPtr& GetEnemys() const noexcept
		{
			return m_Enemys;
		}

		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}