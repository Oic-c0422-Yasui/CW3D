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
		//TODO:�{�X��ǉ�����
		ClearTermProvider():
			m_DivisionCurrentTime(0.0f),
			m_EnemyCount(0),
			m_EnemyMaxCount(0)
		{
			
		}
		~ClearTermProvider() {
		}

		/**
		 * @brief		���ݎ��Ԏ擾
		 */
		float GetDivisionTime() const noexcept 
		{
			return m_DivisionCurrentTime;
		}

		/**
		 * @brief		���ݎ��Ԑݒ�
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
		 * @brief		�G�擾
		 */
		size_t GetEnemyCount() const noexcept
		{
			return m_EnemyCount;
		}

		/**
		 * @brief		�G�擾
		 */
		size_t GetEnemyMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}
		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}