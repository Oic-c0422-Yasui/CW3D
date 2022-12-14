#pragma once
#include <functional>
#include <vector>
#include "GameDefine.h"

namespace ActionGame
{
	//タスクの優先順位（数字が低いほど優先される）
	enum Task_Priority
	{
		TASK_EVENT,		//イベントタスク
		TASK_MAIN1,		//メインタスク１
		TASK_MAIN2,		//メインタスク２
		TASK_MAIN3,		//メインタスク３
		TASK_COLLISION,	//衝突タスク
	};
	//タスク関数
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
		bool	m_EndFlg;
	public:
		/*
		* @param	name	タスク名
		* @param	pri		タスク優先順位（数字が低いほど優先順位が高い）
		* @param	func	タスク関数
		*/
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
		/*
		* @brief	タスクが終了したか？
		* @return	true　なら終了
		*/
		bool IsEnd() const noexcept
		{
			return m_EndFlg;
		}
		/*
		* @brief	タスクを終了する
		*/
		void End()  noexcept
		{
			m_EndFlg = true;
		}

	};
	
	using TaskPtr = std::shared_ptr<Task>;
	using TaskList = std::vector<TaskPtr>;
}


