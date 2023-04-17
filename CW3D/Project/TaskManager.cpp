#include "TaskManager.h"



Task::CTaskManager::CTaskManager()
	:taskList_()
	, listLock_()
{
}

Task::CTaskManager::~CTaskManager()
{
	DeleteAllTaskImmediate();
}

void Task::CTaskManager::Excution()
{
	for (size_t i = 0; i < taskList_.size(); i++)
	{
		if (!taskList_[i]->IsEnd())
		{
			taskList_[i]->Execution();
		}
	}
	//終了したタスクを削除する
	DeleteTask();
}

void Task::CTaskManager::Sort()
{
	//タスクの優先度順にソート
	std::sort(taskList_.begin(), taskList_.end(),
		[](TaskPtr& task1, TaskPtr& task2)
		{
			return task1->GetPriority() < task2->GetPriority();
		});
}

void Task::CTaskManager::AddTask(const std::string& key, PRIORITY pri,Func func)
{
	std::lock_guard<std::mutex> guard(listLock_);
	auto task = std::make_shared<CTask>(key, pri, func);
	taskList_.push_back(task);
	
	//タスクをソート
	Sort();
}

void Task::CTaskManager::DeleteTask(const std::string& key)
{
	auto it = std::find_if(taskList_.begin(), taskList_.end(), [&](const TaskPtr& task) {
		return task->GetName() == key; });
	if (it != taskList_.end())
	{
		(*it)->End();
	}
}

void Task::CTaskManager::DeleteTaskImmediate(const std::string& key)
{
	std::lock_guard<std::mutex> guard(listLock_);
	auto removeIt = std::remove_if(taskList_.begin(), taskList_.end(), [&](const TaskPtr& task) {
		return task->GetName() == key; });
	taskList_.erase(removeIt, taskList_.end());
}

const Task::TaskPtr& Task::CTaskManager::GetTask(const std::string& key)
{
	for (auto& task : taskList_)
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
	for (auto task : taskList_)
	{
		task->End();
	}
}

void Task::CTaskManager::DeleteAllTaskImmediate()
{
	std::lock_guard<std::mutex> guard(listLock_);
	taskList_.clear();
}


void Task::CTaskManager::DeleteTask()
{
	std::lock_guard<std::mutex> guard(listLock_);
	auto removeIt = std::remove_if(taskList_.begin(), taskList_.end(), [&](const TaskPtr& task) {
		return task->IsEnd(); });
	taskList_.erase(removeIt, taskList_.end());
}