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
		int				interval;

		//待機時間
		int				currentTime;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		AICycleFixed(int wait)
			: interval(wait)
			, currentTime(0)
		{
		}

		/**
		 * @brief		更新
		 * @return		trueなら出現
		 */
		bool Update() override {
			currentTime++;
			if (currentTime > interval)
			{
				currentTime -= interval;
				return true;
			}
			return false;
		}

		/**
		 * @brief		状態リセット
		 */
		void Reset() override {
			currentTime = 0;
		}
	};
}