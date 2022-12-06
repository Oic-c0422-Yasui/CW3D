#pragma once
#include "Task.h"
#include	<algorithm>

namespace ActionGame
{

	class TaskManager
	{
	private:
		TaskList m_TaskList;
		std::mutex m_ListLock;

	public:
		TaskManager();
		~TaskManager();

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
		void AddTask(const std::string& key, Task_Priority pri, Func func);

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
		* @brief	�^�X�N���擾����
		* @param	key �^�X�N�̖��O
		* @return	�^�X�N�N���X
		*/
		const TaskPtr& GetTask(const std::string& key);

		/*
		* @brief	�^�X�N�𑦎��j������
		*/
		void ClearTaskImmediate()
		{
			std::lock_guard<std::mutex> guard(m_ListLock);
			m_TaskList.clear();
		}

		/*
		* @brief	�^�X�N�����ׂč폜����
		* @param	key �^�X�N�̖��O
		*/
		void DeleteAllTask();

	};

}

