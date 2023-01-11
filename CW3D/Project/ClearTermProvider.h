#pragma once
#include <memory>

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
		size_t m_BossCount;
		size_t m_BossMaxCount;
	public:

		ClearTermProvider():
			m_DivisionCurrentTime(0.0f),
			m_EnemyCount(0),
			m_EnemyMaxCount(0),
			m_BossCount(0),
			m_BossMaxCount(0)
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

		void SetBossCount(size_t count) noexcept
		{
			m_BossCount = count;
		}

		void SetEnemyMaxCount(size_t count) noexcept
		{
			m_EnemyMaxCount = count;
		}

		void SetBossMaxCount(size_t count) noexcept
		{
			m_BossMaxCount = count;
		}

		/**
		 * @brief		敵数取得
		 */
		size_t GetEnemyCount() const noexcept
		{
			return m_EnemyCount;
		}

		/**
		 * @brief		敵最大数取得
		 */
		size_t GetEnemyMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}

		/**
		 * @brief		ボス数取得
		 */
		size_t GetBossCount() const noexcept
		{
			return m_EnemyMaxCount;
		}

		/**
		 * @brief		ボス最大数取得
		 */
		size_t GetBossMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}
		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}