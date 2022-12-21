#pragma once


#include "EnemyBuildParameter.h"
#include "Object.h"
#include "IClearTerm.h"
#include "EnemySpawner.h"


namespace ActionGame
{
	/*
	* @brief	�X�e�[�W����؂邽�߂̃N���X
	*/
	class CDivision
	{
	public:
		//���f�[�^
		struct DIVISION_DATA
		{
			ClearTermArray	ClearTerms;					//�N���A����
			EnemyBuildParameterArrayPtr EnemysParam;	//�G�����p�����[�^
			Spawner::EnemySpawnerArrayPtr EnemySpawners;	//�G�X�|�i�[
			int EnemyCount;								//��������G�̐�
			std::vector<ObjectPtr> Objects;				//���I�u�W�F�N�g
			int ObjectCount;							//���I�u�W�F�N�g�̐�

			float width;
		};
	private:
		DIVISION_DATA m_Data;
		bool m_ClearFlg;
	public:
		CDivision(DIVISION_DATA data);
		~CDivision();

		/*
		* @brief	������
		*/
		void Initialize();
		/*
		* @brief	�X�V
		*/
		void Update();
		/*
		* @brief	���
		*/
		void Release();
		
		/*
		* @brief	�G�̐����p�����[�^�擾
		* @return	�G�̐����f�[�^
		*/
		const EnemyBuildParameterArrayPtr& GetEnemysParam()
		{
			return m_Data.EnemysParam;
		}

		/*
		* @brief	�G�̃X�|�i�[�擾
		* @return	�G�̃X�|�i�[
		*/
		const Spawner::EnemySpawnerArrayPtr& GetEnemySpawners()
		{
			return m_Data.EnemySpawners;
		}

		/*
		* @brief	���I�u�W�F�N�g�擾
		* @param	id �z��ԍ�
		* @return	���I�u�W�F�N�g
		*/
		const ObjectPtr& GetObj(size_t id)
		{
			assert(m_Data.Objects[id]);
			return m_Data.Objects[id];
		}

		/*
		* @brief	���I�u�W�F�N�g���擾
		* @return	���I�u�W�F�N�g��
		*/
		int GetObjCount() const noexcept
		{
			return m_Data.ObjectCount;
		}

		/*
		* @brief	��������G�̐��擾
		* @return	��������G�̐�
		*/
		int GetEnemyCount() const noexcept
		{
			return m_Data.EnemyCount;
		}

		/*
		* @brief	���I�u�W�F�N�g�����ׂĔj������
		*/
		void ClearObject() noexcept
		{
			SetShowObjects(false);
		}

		/*
		* @brief	���I�u�W�F�N�g�̕\���ݒ�
		* @param	isShow �\����
		*/
		void SetShowObjects(bool isShow) noexcept
		{
			for (auto& object : m_Data.Objects)
			{
				object->SetShow(isShow);
			}
		}

		/*
		* @brief	�����N���A���Ă��邩�H
		* @param	provider	�N���A�����ɕK�v�ȃp�����[�^��񋟂���v���o�C�_
		* @return	true�@�Ȃ�N���A
		*/
		bool IsClear(const ClearTermProviderPtr& provider);
	};

	using DivisionPtr = std::shared_ptr<CDivision>;
	using DivisionArray = std::vector<DivisionPtr>;
	using DivisionArrayPtr = std::shared_ptr<DivisionArray>;
}


