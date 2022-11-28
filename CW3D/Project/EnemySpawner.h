#pragma once

#include	<vector>
#include	"ISpawnCondition.h"
#include	"ISpawnCycle.h"
#include	"EnemyBuilder.h"
#include	"EnemySpawnParameter.h"


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
		EnemySpawnParameter			m_EnemyParam;
		//出現オブジェクト生成
		Sample::EnemyBuilderPtr		m_Builder;
		//出現オブジェクトリスト
		Sample::EnemyArrayPtr		m_Enemys;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		EnemySpawner(const SpawnConditionArray& conditions,
			SpawnCyclePtr cycle, 
			EnemySpawnParameter param,
			Sample::EnemyBuilderPtr builder,
			Sample::EnemyArrayPtr enemys)
			: m_Conditions(conditions)
			, m_Cycle(cycle)
			, m_EnemyParam(param)
			, m_Builder(builder)
			, m_Enemys(enemys)
		{
		}

		/**
		 * @brief		更新
		 */
		void Update() {
			//どれか一つでも条件を満たさないなら実行しない
			if (!IsValid())
			{
				return;
			}
			while (m_Cycle->Update())
			{
				Spawn(m_EnemyParam.GetParameter());
				m_EnemyParam.Next();
			}
		}

		/**
		 * @brief		スポーン
		 */
		Sample::EnemyPtr Spawn(const Sample::EnemyBuildParameterPtr& param)
		{
			auto obj = m_Builder->Create(param);
			m_Enemys->push_back(obj);

			return obj;
		}

		/**
		 * @brief		状態リセット
		 */
		void Reset() {
			m_Cycle->Reset();
		}

		/**
		 * @brief		有効判定
		 */
		bool IsValid() const {
			for (auto& condition : m_Conditions)
			{
				if (!condition->IsValid())
				{
					return false;
				}
			}
			return true;
		}
	};
	//ポインタ置き換え
	using EnemySpawnerPtr = std::shared_ptr<EnemySpawner>;
	using EnemySpawnerArray = std::vector<EnemySpawner>;
}
