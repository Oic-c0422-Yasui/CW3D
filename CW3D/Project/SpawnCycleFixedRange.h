#pragma once
#include "ISpawnCycle.h"
#include "CharaTypeDefine.h"

namespace Spawner
{
	/**
	 * @brief		出現周期決定処理
	 */
	class SpawnCycleFixedRange : public ISpawnCycle
	{
	private:

		//間隔
		float			m_Interval;

		//待機時間
		float			m_CurrentTime;

		CHARA_TYPE		m_Type;
	public:
		/**
		 *	@brief		コンストラクタ
		 */
		SpawnCycleFixedRange(int interval,CHARA_TYPE type);

		/**
		 * @brief		更新
		 * @return		trueなら出現
		 */
		bool Update() override;

		/**
		 * @brief		状態リセット
		 */
		void Reset() override {
			m_CurrentTime = 0;
		}
	};

}

