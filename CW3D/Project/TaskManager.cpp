#include "TaskManager.h"

ActionGame::TaskManager::TaskManager()
	:m_TaskList()
{
}

ActionGame::TaskManager::~TaskManager()
{
	ResetTask();
}

void ActionGame::TaskManager::Excution()
{

	for (auto task : m_TaskList)
	{
		task->Execution();
	}
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
	auto task = std::make_shared<Task>(key, pri, func);

	m_TaskList.push_back(task);
	Sort();
}

void ActionGame::TaskManager::DeleteTask(const std::string& key)
{
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


