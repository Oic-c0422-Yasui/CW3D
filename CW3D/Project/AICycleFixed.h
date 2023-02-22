#pragma once

#include	"IAICycle.h"

namespace ActionGame
{
	/**
	 * @brief		固定周期決定処理
	 */
	class AICycleFixed : public IAICycle
	{
	private:
		//間隔
		int				m_Interval;

		//待機時間
		int				currentTime_;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		AICycleFixed(int wait)
			: m_Interval(wait)
			, currentTime_(0)
		{
		}

		/**
		 * @brief		更新
		 * @return		trueなら出現
		 */
		bool Update() override {
			currentTime_++;
			if (currentTime_ > m_Interval)
			{
				currentTime_ -= m_Interval;
				return true;
			}
			return false;
		}

		/**
		 * @brief		状態リセット
		 */
		void Reset() override {
			currentTime_ = 0;
		}
	};
}