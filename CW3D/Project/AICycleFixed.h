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
		int				m_CurrentTime;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		AICycleFixed(int wait)
			: m_Interval(wait)
			, m_CurrentTime(0)
		{
		}

		/**
		 * @brief		更新
		 * @return		trueなら出現
		 */
		bool Update() override {
			m_CurrentTime++;
			if (m_CurrentTime > m_Interval)
			{
				m_CurrentTime -= m_Interval;
				return true;
			}
			return false;
		}

		/**
		 * @brief		状態リセット
		 */
		void Reset() override {
			m_CurrentTime = 0;
		}
	};
}