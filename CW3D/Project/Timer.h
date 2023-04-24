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
		ParameterHandle< CReactiveParameter<float>>	currentTime_;
		float	targetTime_;
		bool	isAchieve_;
		bool	isStop_;
	public:
		CTimer();
		~CTimer();

		/**
		 * @brief		タイマー開始（目標時間なし）
		 */
		void Start();
		/**
		 * @brief		タイマー開始（目標時間あり）
		 * @param		目標時間
		 */
		void Start(float targetTime);
		/*
		* @brief	タイマー停止
		*/
		void Stop();
		/*
		* @brief	更新
		*/
		void Update();
		/*
		* @brief	キャラのタイムスケールに合わせた更新
		* @param	キャラのタイプ
		*/
		void Update(CHARA_TYPE timeScaleType);
		/*
		* @brief	リセット
		*/
		void Reset();

		/**
		 * @brief		目標時間を達成しているか？
		 * @return		目標時間達成判定
		 */
		bool IsAchieve() const noexcept
		{
			return isAchieve_;
		}

		bool IsTimerStop() const noexcept
		{
			return isStop_;
		}

		/**
		 * @brief		現在時間のサブスクライブ
		 */
		IObservable<float>& GetTimeSubject()
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
			return targetTime_;
		}

		/**
		 * @brief		目標時間設定
		 * @param		目標時間
		 */
		void SetTargetTime(float time) noexcept
		{
			targetTime_ = time;
		}
	};

}

