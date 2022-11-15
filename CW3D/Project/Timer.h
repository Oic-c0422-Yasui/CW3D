#pragma once
#include "Common.h"
#include "TimeScaleController.h"

namespace Sample
{

	class CTimer
	{
	private:
		float	m_CurrentTime;
		float	m_TargetTime;
		bool	m_AchieveFlg;
		bool	m_StopFlg;
	public:
		CTimer();
		~CTimer();

		/**
		 * @brief		タイマー開始
		 */
		void Start();
		/**
		 * @brief		タイマー開始
		 * @param		目標時間
		 */
		void Start(float targetTime);



		void Stop();

		void Update();

		void Update(CHARACTER_TYPE timeScaleType);

		/**
		 * @brief		目標時間を達成しているか？
		 * @return		目標時間達成判定
		 */
		bool IsAchieve() const noexcept
		{
			return m_AchieveFlg;
		}

		bool IsTimerStop() const noexcept
		{
			return m_StopFlg;
		}

		/**
		 * @brief		現在時間取得
		 * @return		現在時間
		 */
		float GetTime() const noexcept
		{
			return m_CurrentTime;
		}

		/**
		 * @brief		目標時間取得
		 * @return		目標時間
		 */
		float GetTargetTime() const noexcept
		{
			return m_TargetTime;
		}

		/**
		 * @brief		目標時間設定
		 * @param		目標時間
		 */
		void SetTargetTime(float time) noexcept
		{
			m_TargetTime = time;
		}
	};

}

