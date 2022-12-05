#pragma once
#include <functional>
#include <vector>
#include "GameDefine.h"

namespace ActionGame
{
	

	using Func = std::function<void()>;
	/*
	* @brief	タスク処理を行う
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
		* @brief	タスク実行
		*/
		void Execution();

		/*
		* @brief	優先順位取得
		* @return	優先順位（数字が低いほど優先順位が高い）
		*/
		Task_Priority GetPriority() const noexcept
		{
			return m_Priority;
		}

		/*
		* @brief	優先順位設定
		* @param	pri	優先順位（数字が低いほど優先順位が高い）
		*/
		void SetPriority(Task_Priority pri) noexcept
		{
			m_Priority = pri;
		}

		/*
		* @brief	タスク名取得
		* @return	タスク名
		*/
		const std::string& GetName() const noexcept
		{
			return m_Name;
		}

	};
	
	using TaskPtr = std::shared_ptr<Task>;
	using TaskList = std::vector<TaskPtr>;
}


