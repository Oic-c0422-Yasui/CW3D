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
		//TODO:ƒ{ƒX‚ğ’Ç‰Á‚·‚é
		ClearTermProvider(const EnemyArrayPtr& enemys):
			m_DivisionCurrentTime(0.0f),
			m_Enemys(enemys)
		{
			
		}
		~ClearTermProvider() {}

		/**
		 * @brief		Œ»İŠÔæ“¾
		 */
		float GetDivisionTime() const noexcept 
		{
			return m_DivisionCurrentTime;
		}

		/**
		 * @brief		Œ»İŠÔİ’è
		 */
		void SetDivisionTime(float time) noexcept
		{
			m_DivisionCurrentTime = time;
		}

		/**
		 * @brief		“Gæ“¾
		 */
		const EnemyArrayPtr& GetEnemys() const noexcept
		{
			return m_Enemys;
		}

		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}