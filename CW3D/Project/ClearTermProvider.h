#pragma once
#include "GameDefine.h"
#include "Enemy.h"

namespace Sample
{
	class ClearTermProvider
	{
	private:
		float m_DivisionCurrentTime;
		EnemyArrayPtr m_Enemys;
	public:
		//TODO:ボスを追加する
		ClearTermProvider(const EnemyArrayPtr& enemys):
			m_DivisionCurrentTime(0.0f),
			m_Enemys(enemys)
		{
			
		}
		~ClearTermProvider() {}

		/**
		 * @brief		現在時間取得
		 */
		float GetDivisionTime() const noexcept 
		{
			return m_DivisionCurrentTime;
		}

		/**
		 * @brief		現在時間設定
		 */
		void SetDivisionTime(float time) noexcept
		{
			m_DivisionCurrentTime = time;
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