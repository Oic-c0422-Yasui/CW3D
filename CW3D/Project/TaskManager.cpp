#include "TaskManager.h"

ActionGame::TaskManager::TaskManager()
	:m_TaskList()
	, m_ListLock()
{
}

ActionGame::TaskManager::~TaskManager()
{
	DeleteAllTaskImmediate();
}

void ActionGame::TaskManager::Excution()
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	for (auto task : m_TaskList)
	{
		if (!task->IsEnd())
		{
			task->Execution();
		}
	}
	auto removeIt = std::remove_if(m_TaskList.begin(), m_TaskList.end(), [&](const TaskPtr& task) {
		return task->IsEnd(); });
	m_TaskList.erase(removeIt, m_TaskList.end());
}

void ActionGame::TaskManager::Sort()
{
	std::sort(m_TaskList.begin(), m_TaskList.end(),
		[](ActionGame::TaskPtr& task1, ActionGame::TaskPtr& task2)
		{
			return task1->GetPriority() < task2->GetPriority();
		});
}

void ActionGame::TaskManager::AddTask(const std::string& key, Task_Priority pri,Func func)
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	auto task = std::make_shared<Task>(key, pri, func);

	m_TaskList.push_back(task);
	Sort();
}

void ActionGame::TaskManager::DeleteTask(const std::string& key)
{
	auto it = std::find_if(m_TaskList.begin(), m_TaskList.end(), [&](const TaskPtr& task) {
		return task->GetName() == key; });
	if (it != m_TaskList.end())
	{
		(*it)->Destroy();
	}
}

void ActionGame::TaskManager::DeleteTaskImmediate(const std::string& key)
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	auto removeIt = std::remove_if(m_TaskList.begin(), m_TaskList.end(), [&](const TaskPtr& task) {
		return task->GetName() == key; });
	m_TaskList.erase(removeIt, m_TaskList.end());
}

const ActionGame::TaskPtr& ActionGame::TaskManager::GetTask(const std::string& key)
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

void ActionGame::TaskManager::DeleteAllTask()
{
	for (auto task : m_TaskList)
	{
		task->Destroy();
	}
}

void ActionGame::TaskManager::DeleteAllTaskImmediate()
{
	std::lock_guard<std::mutex> guard(m_ListLock);
	m_TaskList.clear();
}


