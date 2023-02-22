#pragma once
#include "ISpawnCycle.h"
#include "Common.h"

namespace Spawner
{
	/**
	 * @brief		出現周期決定処理
	 */
	class SpawnCycleRandomRange : public ISpawnCycle
	{
	private:
		//間隔最小
		int				m_IntervalMin;
		//間隔最大
		int				m_IntervalMax;

		//現在の間隔
		float			m_CurrentInterval;

		//待機時間
		float			currentTime_;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		SpawnCycleRandomRange(int min, int max);

		/**
		 * @brief		更新
		 * @return		trueなら出現
		 */
		bool Update() override;

		/**
		 * @brief		状態リセット
		 */
		void Reset() override {
			currentTime_ = 0;
		}
	};
    
}


