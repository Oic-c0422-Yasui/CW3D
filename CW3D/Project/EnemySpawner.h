#pragma once

#include	<vector>
#include	"ISpawnCondition.h"
#include	"ISpawnCycle.h"
#include	"EnemyBuilder.h"
#include	"EnemySpawnParameter.h"


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
		//�o���I�u�W�F�N�g����
		Sample::EnemyBuilderPtr		m_Builder;
		//�o���I�u�W�F�N�g���X�g
		Sample::EnemyArrayPtr		m_Enemys;

	public:
		/**
		 * @brief		�R���X�g���N�^
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
		 * @brief		�X�V
		 */
		void Update() {
			//�ǂꂩ��ł������𖞂����Ȃ��Ȃ���s���Ȃ�
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
		 * @brief		�X�|�[��
		 */
		Sample::EnemyPtr Spawn(const Sample::EnemyBuildParameterPtr& param)
		{
			auto obj = m_Builder->Create(param);
			m_Enemys->push_back(obj);

			return obj;
		}

		/**
		 * @brief		��ԃ��Z�b�g
		 */
		void Reset() {
			m_Cycle->Reset();
		}

		/**
		 * @brief		�L������
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
	//�|�C���^�u������
	using EnemySpawnerPtr = std::shared_ptr<EnemySpawner>;
	using EnemySpawnerArray = std::vector<EnemySpawner>;
}
