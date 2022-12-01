#include "Task.h"

Sample::Task::Task(const std::string& name, Task_Priority pri,  const Func& func)
	: m_Priority(pri)
	, m_Name(name)
	, m_Task(func)
{
}

Sample::Task::~Task()
{
}

void Sample::Task::Execution()
{
	m_Task();
}
