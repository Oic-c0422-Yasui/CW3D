#pragma once
#include "Task.h"
#include	<algorithm>
#include	<mutex>

namespace Task
{
	/*
	* @brief	タスク管理を行うクラス
	*/
	class CTaskManager
	{
	private:
		TaskList taskList_;
		std::mutex listLock_;

	private:
		/* プライベート関数　*/

		//終了したタスクを削除する
		void DeleteTask();

	public:
		CTaskManager();
		~CTaskManager();

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
		void AddTask(const std::string& key, PRIORITY pri, Func func);

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
		* @brief	タスクをすべて削除する
		*/
		void DeleteAllTask();
		/*
		* @brief	タスクをすべて即時削除する
		*/
		void DeleteAllTaskImmediate();

		/*
		* @brief	タスクを取得する
		* @param	key タスクの名前
		* @return	タスククラス
		*/
		const TaskPtr& GetTask(const std::string& key);

	};

}

