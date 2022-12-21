#pragma once


#include	"ISpawnCondition.h"
#include	"ISpawnCycle.h"

#include	"Enemy.h"


namespace Spawner
{
	/**
	 * @brief		�o������
	 */
	class EnemySpawner
	{
	private:
		//�o������
		SpawnConditionArray			m_Conditions;
		//�o���p�T�C�N��
		SpawnCyclePtr				m_Cycle;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EnemySpawner(const SpawnConditionArray& conditions,
					SpawnCyclePtr cycle);

		/**
		 * @brief		�X�V
		 */
		void Update(const ActionGame::EnemyPtr& enemy);

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset();

		/**
		 * @brief		�L������
		 */
		bool IsValid() const;
	};
	//�|�C���^�u������
	using EnemySpawnerPtr = std::shared_ptr<EnemySpawner>;
	using EnemySpawnerArray = std::vector<EnemySpawnerPtr>;
	using EnemySpawnerArrayPtr = std::shared_ptr<EnemySpawnerArray>;
}
