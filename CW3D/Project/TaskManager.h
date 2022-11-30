#pragma once
#include "Task.h"
#include	<algorithm>
#include	<map>

namespace Sample
{

	class TaskManager
	{
	private:
		std::map<std::string, TaskPtr> m_TaskList;
	public:
		TaskManager();
		~TaskManager();

		void Excution();
		void Sort();
		void AddTask(const std::string& key, int pri, Func func);
		bool DeleteTask(const std::string& key);

	};

}

