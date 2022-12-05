#pragma once
#include <functional>
#include <vector>
#include "GameDefine.h"

namespace ActionGame
{
	

	using Func = std::function<void()>;
	/*
	* @brief	�^�X�N�������s��
	*/
	class Task
	{
	private:
		Task_Priority m_Priority;
		Func m_Task;
		std::string	m_Name;
	public:

		Task(const std::string& name, Task_Priority pri, const Func& func);
		~Task();

		/*
		* @brief	�^�X�N���s
		*/
		void Execution();

		/*
		* @brief	�D�揇�ʎ擾
		* @return	�D�揇�ʁi�������Ⴂ�قǗD�揇�ʂ������j
		*/
		Task_Priority GetPriority() const noexcept
		{
			return m_Priority;
		}

		/*
		* @brief	�D�揇�ʐݒ�
		* @param	pri	�D�揇�ʁi�������Ⴂ�قǗD�揇�ʂ������j
		*/
		void SetPriority(Task_Priority pri) noexcept
		{
			m_Priority = pri;
		}

		/*
		* @brief	�^�X�N���擾
		* @return	�^�X�N��
		*/
		const std::string& GetName() const noexcept
		{
			return m_Name;
		}

	};
	
	using TaskPtr = std::shared_ptr<Task>;
	using TaskList = std::vector<TaskPtr>;
}


