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
			ClearTerm::ClearTermArray	ClearTerms;		//�N���A����
			EnemyBuildParameterArrayPtr EnemysParam;	//�G�����p�����[�^
			Spawner::EnemySpawnerArrayPtr EnemySpawners;	//�G�X�|�i�[
			size_t EnemyCount;								//��������G�̐�
			std::vector<ObjectPtr> Objects;				//���I�u�W�F�N�g
			size_t ObjectCount;							//���I�u�W�F�N�g�̐�

			float width;
		};
	private:
		DIVISION_DATA data_;
		bool isClear_;
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
			return data_.EnemysParam;
		}

		/*
		* @brief	�G�̃X�|�i�[�擾
		* @return	�G�̃X�|�i�[
		*/
		const Spawner::EnemySpawnerArrayPtr& GetEnemySpawners()
		{
			return data_.EnemySpawners;
		}

		/*
		* @brief	���I�u�W�F�N�g�擾
		* @param	id �z��ԍ�
		* @return	���I�u�W�F�N�g
		*/
		const ObjectPtr& GetObj(size_t id)
		{
			assert(data_.Objects[id]);
			return data_.Objects[id];
		}

		/*
		* @brief	���I�u�W�F�N�g���擾
		* @return	���I�u�W�F�N�g��
		*/
		size_t GetObjCount() const noexcept
		{
			return data_.ObjectCount;
		}

		/*
		* @brief	��������G�̐��擾
		* @return	��������G�̐�
		*/
		size_t GetEnemyCount() const noexcept
		{
			return data_.EnemyCount;
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
			for (auto& object : data_.Objects)
			{
				object->SetShow(isShow);
			}
		}

		/*
		* @brief	�����N���A���Ă��邩�H
		* @param	provider	�N���A�����ɕK�v�ȃp�����[�^��񋟂���v���o�C�_
		* @return	true�@�Ȃ�N���A
		*/
		bool IsClear(const ClearTerm::ProviderPtr& provider);
	};

	using DivisionPtr = std::shared_ptr<CDivision>;
	using DivisionArray = std::vector<DivisionPtr>;
	using DivisionArrayPtr = std::shared_ptr<DivisionArray>;
}


