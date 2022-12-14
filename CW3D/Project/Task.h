#pragma once
#include <functional>
#include <vector>
#include "GameDefine.h"

namespace ActionGame
{
	//�^�X�N�̗D�揇�ʁi�������Ⴂ�قǗD�悳���j
	enum Task_Priority
	{
		TASK_EVENT,		//�C�x���g�^�X�N
		TASK_MAIN1,		//���C���^�X�N�P
		TASK_MAIN2,		//���C���^�X�N�Q
		TASK_MAIN3,		//���C���^�X�N�R
		TASK_COLLISION,	//�Փ˃^�X�N
	};
	//�^�X�N�֐�
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
		bool	m_EndFlg;
	public:
		/*
		* @param	name	�^�X�N��
		* @param	pri		�^�X�N�D�揇�ʁi�������Ⴂ�قǗD�揇�ʂ������j
		* @param	func	�^�X�N�֐�
		*/
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
		/*
		* @brief	�^�X�N���I���������H
		* @return	true�@�Ȃ�I��
		*/
		bool IsEnd() const noexcept
		{
			return m_EndFlg;
		}
		/*
		* @brief	�^�X�N���I������
		*/
		void End()  noexcept
		{
			m_EndFlg = true;
		}

	};
	
	using TaskPtr = std::shared_ptr<Task>;
	using TaskList = std::vector<TaskPtr>;
}


