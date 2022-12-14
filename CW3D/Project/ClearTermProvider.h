#pragma once

#include "Enemy.h"

namespace ActionGame
{
	/*
	* @brief	クリア条件に必要なパラメータを提供する
	*/
	class ClearTermProvider
	{
	private:
		float m_DivisionCurrentTime;
		size_t m_EnemyCount;
		size_t m_EnemyMaxCount;
	public:
		//TODO:ボスを追加する
		ClearTermProvider():
			m_DivisionCurrentTime(0.0f),
			m_EnemyCount(0),
			m_EnemyMaxCount(0)
		{
			
		}
		~ClearTermProvider() {
		}

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

		void SetEnemyCount(size_t count) noexcept
		{
			m_EnemyCount = count;
		}

		void SetEnemyMaxCount(size_t count) noexcept
		{
			m_EnemyMaxCount = count;
		}

		/**
		 * @brief		敵取得
		 */
		size_t GetEnemyCount() const noexcept
		{
			return m_EnemyCount;
		}

		/**
		 * @brief		敵取得
		 */
		size_t GetEnemyMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}
		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}