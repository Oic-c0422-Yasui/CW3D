#pragma once


#include	"ISpawnCondition.h"
#include	"ISpawnCycle.h"

#include	"Enemy.h"


namespace Spawner
{
	/**
	 * @brief		出現処理
	 */
	class CEnemySpawner
	{
	private:
		//出現条件
		SpawnConditionArray			conditions_;
		//出現用サイクル
		SpawnCyclePtr				cycle_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CEnemySpawner(const SpawnConditionArray& conditions,
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
	using EnemySpawnerPtr = std::shared_ptr<CEnemySpawner>;
	using EnemySpawnerArray = std::vector<EnemySpawnerPtr>;
	using EnemySpawnerArrayPtr = std::shared_ptr<EnemySpawnerArray>;
}
