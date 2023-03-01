#include "Task.h"

Task::CTask::CTask(const std::string& name, PRIORITY pri,  const Func& func)
	: priority_(pri)
	, name_(name)
	, task_(func)
	, isEnd_(false)
{
}

Task::CTask::~CTask()
{
}

void Task::CTask::Execution()
{
	task_();
}
