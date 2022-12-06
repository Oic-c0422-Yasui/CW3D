#include "Task.h"

ActionGame::Task::Task(const std::string& name, Task_Priority pri,  const Func& func)
	: m_Priority(pri)
	, m_Name(name)
	, m_Task(func)
	, m_EndFlg(false)
{
}

ActionGame::Task::~Task()
{
}

void ActionGame::Task::Execution()
{
	m_Task();
}
