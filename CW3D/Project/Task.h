#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <string>

namespace Task
{
	//�^�X�N�̗D�揇�ʁi�������Ⴂ�قǗD�悳���j
	enum class PRIORITY
	{
		EVENT,		//�C�x���g�^�X�N
		MAIN1,		//���C���^�X�N�P
		MAIN2,		//���C���^�X�N�Q
		MAIN3,		//���C���^�X�N�R
		COLLISION1,	//�Փ˃^�X�N�P
		COLLISION2,	//�Փ˃^�X�N�Q
	};
	//�^�X�N�֐�
	using Func = std::function<void()>;


	/*
	* @brief	�^�X�N�������s��
	*/
	class CTask
	{
	private:
		PRIORITY priority_;
		Func task_;
		std::string	name_;
		bool	isEnd_;
	public:
		/*
		* @param	name	�^�X�N��
		* @param	pri		�^�X�N�D�揇�ʁi�������Ⴂ�قǗD�揇�ʂ������j
		* @param	func	�^�X�N�֐�
		*/
		CTask(const std::string& name, PRIORITY pri, const Func& func);
		~CTask();

		/*
		* @brief	�^�X�N���s
		*/
		void Execution();

		/*
		* @brief	�D�揇�ʎ擾
		* @return	�D�揇�ʁi�������Ⴂ�قǗD�揇�ʂ������j
		*/
		PRIORITY GetPriority() const noexcept
		{
			return priority_;
		}

		/*
		* @brief	�D�揇�ʐݒ�
		* @param	pri	�D�揇�ʁi�������Ⴂ�قǗD�揇�ʂ������j
		*/
		void SetPriority(PRIORITY pri) noexcept
		{
			priority_ = pri;
		}

		/*
		* @brief	�^�X�N���擾
		* @return	�^�X�N��
		*/
		const std::string& GetName() const noexcept
		{
			return name_;
		}
		/*
		* @brief	�^�X�N���I���������H
		* @return	true�@�Ȃ�I��
		*/
		bool IsEnd() const noexcept
		{
			return isEnd_;
		}
		/*
		* @brief	�^�X�N���I������
		*/
		void End()  noexcept
		{
			isEnd_ = true;
		}

	};
	
	using TaskPtr = std::shared_ptr<CTask>;
	using TaskList = std::vector<TaskPtr>;
}


