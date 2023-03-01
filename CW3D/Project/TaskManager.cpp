#include "TaskManager.h"



Task::CTaskManager::CTaskManager()
	:m_TaskList()
	, m_ListLock()
{
}

Task::CTaskManager::~CTaskManager()
{
	DeleteAllTaskImmediate();
}

void Task::CTaskManager::Excution()
{
	for (size_t i = 0; i < m_TaskList.size(); i++)
	{
		if (!m_TaskList[i]->IsEnd())
		{
			m_TaskList[i]->Execution();
		}
	}
	//終了したタスクを削除する
	DeleteTask();
}

void Task::CTaskManager::Sort()
{
	//タスクの優先度順にソート
	std::sort(m_TaskList.begin(), m_TaskList.end(),
		[](TaskPtr& task1, TaskPtr& task2)
		{
			return task1->GetPriority() < task2->GetPriority();
		});
}

void Task::CTaskManager::AddTask(const std::string& key, PRIORITY pri,Func func)
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	auto task = std::make_shared<CTask>(key, pri, func);
	m_TaskList.push_back(task);
	
	//タスクをソート
	Sort();
}

void Task::CTaskManager::DeleteTask(const std::string& key)
{
	auto it = std::find_if(m_TaskList.begin(), m_TaskList.end(), [&](const TaskPtr& task) {
		return task->GetName() == key; });
	if (it != m_TaskList.end())
	{
		(*it)->End();
	}
}

void Task::CTaskManager::DeleteTaskImmediate(const std::string& key)
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	auto removeIt = std::remove_if(m_TaskList.begin(), m_TaskList.end(), [&](const TaskPtr& task) {
		return task->GetName() == key; });
	m_TaskList.erase(removeIt, m_TaskList.end());
}

const Task::TaskPtr& Task::CTaskManager::GetTask(const std::string& key)
{
	for (auto& task : m_TaskList)
	{
		if (task->GetName() == key)
		{
			return task;
		}
	}
	return nullptr;
}

void Task::CTaskManager::DeleteAllTask()
{
	for (auto task : m_TaskList)
	{
		task->End();
	}
}

void Task::CTaskManager::DeleteAllTaskImmediate()
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	m_TaskList.clear();
}


void Task::CTaskManager::DeleteTask()
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	auto removeIt = std::remove_if(m_TaskList.begin(), m_TaskList.end(), [&](const TaskPtr& task) {
		return task->IsEnd(); });
	m_TaskList.erase(removeIt, m_TaskList.end());
}