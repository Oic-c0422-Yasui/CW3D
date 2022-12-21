#pragma once


#include	"ISpawnCondition.h"
#include	"ISpawnCycle.h"

#include	"Enemy.h"


namespace Spawner
{
	/**
	 * @brief		出現処理
	 */
	class EnemySpawner
	{
	private:
		//出現条件
		SpawnConditionArray			m_Conditions;
		//出現用サイクル
		SpawnCyclePtr				m_Cycle;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		EnemySpawner(const SpawnConditionArray& conditions,
					SpawnCyclePtr cycle);

		/**
		 * @brief		更新
		 */
		void Update(const ActionGame::EnemyPtr& enemy);

		/**
		 * @brief		状態リセット
		 */
		void Reset();

		/**
		 * @brief		有効判定
		 */
		bool IsValid() const;
	};
	//ポインタ置き換え
	using EnemySpawnerPtr = std::shared_ptr<EnemySpawner>;
	using EnemySpawnerArray = std::vector<EnemySpawnerPtr>;
	using EnemySpawnerArrayPtr = std::shared_ptr<EnemySpawnerArray>;
}
