#pragma once

#include	<vector>
#include	"ISpawnCondition.h"
#include	"ISpawnCycle.h"
#include	"EnemySpawnParameter.h"
#include	"EnemyManager.h"
#include	"EnemyBuilderDictionary.h"


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
		EnemySpawnParameterPtr			m_EnemyParam;
		//出現オブジェクトリスト
		ActionGame::EnemyArrayPtr		m_Enemys;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		EnemySpawner(const SpawnConditionArray& conditions,
					SpawnCyclePtr cycle,
					EnemySpawnParameterPtr param);

		/**
		 * @brief		更新
		 */
		void Update(ActionGame::EnemyManager& manager);

		/**
		 * @brief		スポーン
		 * @param		param 敵生成のパラメータ
		 */
		ActionGame::EnemyPtr Spawn(const ActionGame::EnemyBuildParameterPtr& param);

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
}
