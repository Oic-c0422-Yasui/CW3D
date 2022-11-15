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
		//TODO:�{�X��ǉ�����
		ClearTermProvider(const EnemyArrayPtr& enemys):
			m_DivisionCurrentTime(0.0f),
			m_Enemys(enemys)
		{
			
		}
		~ClearTermProvider() {}

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

		/**
		 * @brief		�G�擾
		 */
		const EnemyArrayPtr& GetEnemys() const noexcept
		{
			return m_Enemys;
		}

		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}