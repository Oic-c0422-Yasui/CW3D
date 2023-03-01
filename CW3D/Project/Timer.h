#pragma once
#include "Common.h"
#include "TimeScaleController.h"
#include "ReactiveParameter.h"
#include "ParameterHandle.h"
#include "Observer.h"

namespace ActionGame
{

	class CTimer
	{
	private:
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float>>	currentTime_;
		float	m_TargetTime;
		bool	m_AchieveFlg;
		bool	isStop_;
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

		void Update(CHARA_TYPE timeScaleType);

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
			return isStop_;
		}

		/**
		 * @brief		現在時間のサブスクライブ
		 */
		ActionGame::IObservable<float>& GetTimeSubject()
		{
			return currentTime_.Get();
		}

		/**
		 * @brief		現在時間取得
		 * @return		現在時間
		 */
		float GetTime() const noexcept
		{
			return currentTime_.Get();
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

