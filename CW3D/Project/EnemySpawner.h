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
		EnemySpawnParameterPtr			m_EnemyParam;
		//�o���I�u�W�F�N�g���X�g
		ActionGame::EnemyArrayPtr		m_Enemys;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EnemySpawner(const SpawnConditionArray& conditions,
					SpawnCyclePtr cycle,
					EnemySpawnParameterPtr param);

		/**
		 * @brief		�X�V
		 */
		void Update(ActionGame::EnemyManager& manager);

		/**
		 * @brief		�X�|�[��
		 * @param		param �G�����̃p�����[�^
		 */
		ActionGame::EnemyPtr Spawn(const ActionGame::EnemyBuildParameterPtr& param);

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
}
