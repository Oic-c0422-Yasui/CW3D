#pragma once
#include "GameDefine.h"
#include "Enemy.h"

namespace Sample
{
	class ClearTermProvider
	{
	private:
		float m_DivisionCurrentTime;
		size_t m_EnemyCount;
		size_t m_EnemyMaxCount;
	public:
		//TODO:ƒ{ƒX‚ğ’Ç‰Á‚·‚é
		ClearTermProvider():
			m_DivisionCurrentTime(0.0f),
			m_EnemyCount(0),
			m_EnemyMaxCount(0)
		{
			
		}
		~ClearTermProvider() {
		}

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

		void SetEnemyCount(size_t count) noexcept
		{
			m_EnemyCount = count;
		}

		void SetEnemyMaxCount(size_t count) noexcept
		{
			m_EnemyMaxCount = count;
		}

		/**
		 * @brief		“Gæ“¾
		 */
		size_t GetEnemyCount() const noexcept
		{
			return m_EnemyCount;
		}

		/**
		 * @brief		“Gæ“¾
		 */
		size_t GetEnemyMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}
		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}