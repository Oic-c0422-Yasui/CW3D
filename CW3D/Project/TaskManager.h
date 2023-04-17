#pragma once
#include "Task.h"
#include	<algorithm>
#include	<mutex>

namespace Task
{
	/*
	* @brief	�^�X�N�Ǘ����s���N���X
	*/
	class CTaskManager
	{
	private:
		TaskList taskList_;
		std::mutex listLock_;

	private:
		/* �v���C�x�[�g�֐��@*/

		//�I�������^�X�N���폜����
		void DeleteTask();

	public:
		CTaskManager();
		~CTaskManager();

		/*
		* @brief	�^�X�N�����s����
		*/
		void Excution();

		/*
		* @brief	�^�X�N��D��x���ɕ��בւ���
		*/
		void Sort();

		/*
		* @brief	�^�X�N��ǉ�����
		* @param	key �^�X�N�̖��O
		* @param	pri	�^�X�N�̗D�揇�ʁi�������Ⴂ�قǗD�悳���j
		* @param	func ���s����^�X�N�ivoid�֐��j
		*/
		void AddTask(const std::string& key, PRIORITY pri, Func func);

		/*
		* @brief	�^�X�N���폜����
		* @param	key �^�X�N�̖��O
		*/
		void DeleteTask(const std::string& key);

		/*
		* @brief	�^�X�N�𑦎��폜����
		* @param	key �^�X�N�̖��O
		*/
		void DeleteTaskImmediate(const std::string& key);
		/*
		* @brief	�^�X�N�����ׂč폜����
		*/
		void DeleteAllTask();
		/*
		* @brief	�^�X�N�����ׂđ����폜����
		*/
		void DeleteAllTaskImmediate();

		/*
		* @brief	�^�X�N���擾����
		* @param	key �^�X�N�̖��O
		* @return	�^�X�N�N���X
		*/
		const TaskPtr& GetTask(const std::string& key);

	};

}

