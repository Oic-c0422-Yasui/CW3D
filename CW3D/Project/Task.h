#pragma once
#include <functional>
#include <vector>

namespace Sample
{
	/*
	* @brief	�^�X�N�������s��
	*/
	using Func = std::function<void()>;
	class Task
	{
	private:
		int m_Priority;
		Func m_Task;
	public:
		Task(int pri, const Func& func);
		~Task();

		/*
		* @brief	�^�X�N���s
		*/
		void Execution();

		/*
		* @brief	�D�揇�ʎ擾
		* @return	�D�揇�ʁi�����������قǗD�揇�ʂ������j
		*/
		int GetPriority() const noexcept
		{
			return m_Priority;
		}

		/*
		* @brief	�D�揇�ʐݒ�
		* @param	pri	�D�揇�ʁi�����������قǗD�揇�ʂ������j
		*/
		void SetPriority(int pri) noexcept
		{
			m_Priority = pri;
		}

	};
	
	using TaskPtr = std::shared_ptr<Task>;
	using TaskList = std::vector<TaskPtr>;
}


