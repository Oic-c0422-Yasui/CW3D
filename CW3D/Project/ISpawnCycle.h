#pragma once

#include	<memory>

namespace Spawner
{
	/**
	 * @brief		出現周期決定処理
	 */
	class __declspec(novtable) ISpawnCycle
	{
	public:
		/**
		 * @brief		更新
		 * @return		trueなら出現
		 */
		virtual bool Update() = 0;
		/**
		 * @brief		状態リセット
		 */
		virtual void Reset() = 0;
	};
	//ポインタ置き換え
	using SpawnCyclePtr = std::shared_ptr<ISpawnCycle>;
}
