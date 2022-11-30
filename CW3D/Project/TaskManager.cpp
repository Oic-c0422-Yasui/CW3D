#include "TaskManager.h"

Sample::TaskManager::TaskManager()
	:m_TaskList()
{
}

Sample::TaskManager::~TaskManager()
{
}

void Sample::TaskManager::Excution()
{
	for (auto it = m_TaskList.begin(); it != m_TaskList.end(); ++it)
	{
		it->second.get()->Execution();
	}
	//for (auto task : m_TaskList)
	//{
	//	task->Execution();
	//}
}

void Sample::TaskManager::Sort()
{
	std::sort(m_TaskList.begin(), m_TaskList.end(),
		[](Sample::TaskPtr& task1, Sample::TaskPtr& task2)
		{
			return task1->GetPriority() > task2->GetPriority();
		});
}

void Sample::TaskManager::AddTask(const std::string& key, int pri,Func func)
{
	auto task = std::make_shared<Task>(func, pri);
	m_TaskList[key] = task;
	Sort();
}

bool Sample::TaskManager::DeleteTask(const std::string& key)
{
	auto it = m_TaskList.find(key);
	if (it != m_TaskList.end())
	{
		m_TaskList.erase(it);
		Sort();
		return true;
	}
	return false;
}


