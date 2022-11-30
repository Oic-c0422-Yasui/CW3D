#include "CreateThread.h"

ThreadCreator::ThreadCreator()
	: m_Thread()
	, m_CompleteFlg(false)
{
}

ThreadCreator::~ThreadCreator()
{
	if (m_Thread.joinable())
	{
		m_Thread.detach();
	}
}

void ThreadCreator::Create(const CreateFunc& func)
{
	if (m_Thread.joinable())
	{
		m_Thread.detach();
	}

	m_CompleteFlg = false;

	m_Thread = std::thread([=](){	func();
									m_CompleteFlg = true; 
								});
}

bool ThreadCreator::IsLoading()
{
	if (!m_Thread.joinable())
	{
		return false;
	}


	return m_CompleteFlg ? false : true;
}

bool ThreadCreator::IsComplete()
{
	if (!m_Thread.joinable())
	{
		return false;
	}

	return m_CompleteFlg ? true : false;
}
