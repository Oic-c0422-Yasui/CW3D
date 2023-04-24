#pragma once
#include "Common.h"
#include "AnimationUtilities.h"
#include "Timer.h"

namespace ActionGame
{
	class CFade
	{
	private:

		BYTE currentValue_;
		BYTE endValue_;
		BYTE startValue_;
		bool isStart_;
		float endTime_;
		CTimer timer_;

	public:
		CFade();
		~CFade();

		/*
		* @brief	初期化
		* @param	startValue　開始アルファ値
		* @param	endTime		終了時間
		* @param	endValue	終了アルファ値
		*/
		void Initialize(BYTE startValue,float endTime, BYTE endValue);
		/*
		* @brief	フェード開始
		*/
		void Start();
		/*
		* @brief	更新
		*/
		void Update();
		/*
		* @brief	リセット
		*/
		void Reset();
		/*
		* @brief	現在のフェード値取得
		*/
		BYTE GetFadeValue() const noexcept;
		/*
		* @brief	フェードが終了しているか？
		*/
		bool IsEnd() const noexcept;
	};
	
}


