#pragma once
#include "Enemy.h"

namespace ActionGame
{
	/*
	* @brief	�G�}�l�[�W���[
	*/
	class CEnemyManager
	{
	private:
		EnemyArrayPtr enemyArray_;
		ActionGame::CReactiveParameter<size_t> enemyCount_;
		ActionGame::CReactiveParameter<size_t> bossCount_;
		ActionGame::CReactiveParameter<size_t> showEnemyCount_;
		size_t enemyMaxCount_;
		size_t bossMaxCount_;
	public:
		CEnemyManager();
		~CEnemyManager();

		/*
		* @brief�@������
		*/
		void Initialize();
		/*
		* @brief	�X�V
		*/
		void Update();
		/*
		* @brief	�`��
		*/
		void Render();
		/*
		* @brief	�f�o�b�O�`��
		*/
		void RenderDebug();
		/*
		* @brief	���
		*/
		void Release();

		/*
		* @brief	�G�̐��擾
		*/
		size_t GetEnemyCount() const noexcept
		{
			return enemyCount_;
		}
		/*
		* @brief	�G�̍ő吔�擾
		*/
		size_t GetEnemyMaxCount() const noexcept
		{
			return enemyMaxCount_;
		}
		/*
		* @brief	�G�̕\�����擾
		*/
		size_t GetShowEnemyCount() const noexcept
		{
			return showEnemyCount_;
		}
		/*
		* @brief	�{�X�̐��擾
		*/
		size_t GetBossCount() const noexcept
		{
			return bossCount_;
		}
		/*
		* @brief	�{�X�̍ő吔�擾
		*/
		size_t GetBossMaxCount() const noexcept
		{
			return bossMaxCount_;
		}


		/*
		* @brief	�G�̐��ʒm
		*/
		ActionGame::IObservable<size_t>& GetEnemyCountSubject()
		{
			return enemyCount_;
		}
		/*
		* @brief	�G�̕\�����ʒm
		*/
		ActionGame::IObservable<size_t>& GetEnemyShowCountSubject()
		{
			return showEnemyCount_;
		}
		/*
		* @brief	�{�X�̐��ʒm
		*/
		ActionGame::IObservable<size_t>& GetBossCountSubject()
		{
			return bossCount_;
		}

		/*
		* @brief	�G�擾
		* @param	num �G�̔z��ԍ�
		*/
		const EnemyPtr& GetEnemy(size_t num)
		{
			assert(enemyArray_->at(num));
			return enemyArray_->at(num);
		}

		/*
		* @brief	�G�ǉ�
		* @param	�G�̃|�C���^
		*/
		void AddEnemy(const EnemyPtr& enemy);

		/*
		* @brief	�G�z�񃊃Z�b�g
		*/
		void ClearEnemyArray();
	};
}

