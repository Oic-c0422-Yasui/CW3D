#include "Task.h"

Sample::Task::Task(int pri,const Func& func)
	: m_Priority(pri)
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
