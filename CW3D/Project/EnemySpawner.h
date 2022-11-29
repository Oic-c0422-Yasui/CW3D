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
	 * @brief		�o������
	 */
	class EnemySpawner
	{
	private:
		//�o������
		SpawnConditionArray			m_Conditions;
		//�o���p�T�C�N��
		SpawnCyclePtr				m_Cycle;
		EnemySpawnParameter			m_EnemyParam;
		//�o���I�u�W�F�N�g���X�g
		Sample::EnemyArrayPtr		m_Enemys;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EnemySpawner(const SpawnConditionArray& conditions,
					SpawnCyclePtr cycle,
					EnemySpawnParameter param);

		/**
		 * @brief		�X�V
		 */
		void Update(Sample::EnemyManager& manager);

		/**
		 * @brief		�X�|�[��
		 * @param		param �G�����̃p�����[�^
		 */
		Sample::EnemyPtr Spawn(const Sample::EnemyBuildParameterPtr& param);

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
	using EnemySpawnerArray = std::vector<EnemySpawner>;
}
