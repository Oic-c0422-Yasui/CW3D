#pragma once


#include	"ISpawnCondition.h"
#include	"ISpawnCycle.h"

#include	"Enemy.h"


namespace Spawner
{
	/**
	 * @brief		�o������
	 */
	class CEnemySpawner
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
		CEnemySpawner(const SpawnConditionArray& conditions,
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
	using EnemySpawnerPtr = std::shared_ptr<CEnemySpawner>;
	using EnemySpawnerArray = std::vector<EnemySpawnerPtr>;
	using EnemySpawnerArrayPtr = std::shared_ptr<EnemySpawnerArray>;
}
