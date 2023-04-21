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

		void Initialize(BYTE startValue,float endTime, BYTE endValue);

		void Start();

		void Update();

		void Reset();

		BYTE GetFadeValue() const noexcept;

		bool IsEnd() const noexcept;
	};
	
}


