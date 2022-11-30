#pragma once
#include <functional>
#include <vector>

namespace Sample
{
	/*
	* @brief	タスク処理を行う
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
		* @brief	タスク実行
		*/
		void Execution();

		/*
		* @brief	優先順位取得
		* @return	優先順位（数字が高いほど優先順位が高い）
		*/
		int GetPriority() const noexcept
		{
			return m_Priority;
		}

		/*
		* @brief	優先順位設定
		* @param	pri	優先順位（数字が高いほど優先順位が高い）
		*/
		void SetPriority(int pri) noexcept
		{
			m_Priority = pri;
		}

	};
	
	using TaskPtr = std::shared_ptr<Task>;
	using TaskList = std::vector<TaskPtr>;
}


