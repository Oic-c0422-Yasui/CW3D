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
		* @brief	タスクを実行する
		*/
		void Excution();

		/*
		* @brief	タスクを優先度順に並べ替える
		*/
		void Sort();

		/*
		* @brief	タスクを追加する
		* @param	key タスクの名前
		* @param	pri	タスクの優先順位（数字が低いほど優先される）
		* @param	func 実行するタスク（void関数）
		*/
		void AddTask(const std::string& key, Task_Priority pri, Func func);

		/*
		* @brief	タスクを削除する
		* @param	key タスクの名前
		*/
		void DeleteTask(const std::string& key);

		/*
		* @brief	タスクを即時削除する
		* @param	key タスクの名前
		*/
		void DeleteTaskImmediate(const std::string& key);

		/*
		* @brief	タスクを取得する
		* @param	key タスクの名前
		* @return	タスククラス
		*/
		const TaskPtr& GetTask(const std::string& key);

		/*
		* @brief	タスクを即時破棄する
		*/
		void ClearTaskImmediate()
		{
			std::lock_guard<std::mutex> guard(m_ListLock);
			m_TaskList.clear();
		}

		/*
		* @brief	タスクをすべて削除する
		* @param	key タスクの名前
		*/
		void DeleteAllTask();

	};

}

