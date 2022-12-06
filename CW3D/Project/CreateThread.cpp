#include "CreateThread.h"

ThreadCreator::ThreadCreator()
	: m_Thread()
	, m_CompleteFlg(false)
{
}

ThreadCreator::~ThreadCreator()
{
m_Thread.join();
	/*if (m_Thread.joinable())
	{
		m_Thread.detach();
	}*/
}

void ThreadCreator::Create(const CreateFunc& func)
{
	if (m_Thread.joinable())
	{
		m_Thread.detach();
	}

	m_CompleteFlg.store(false);

	m_Thread = std::thread([=]()
				{	func();
					m_CompleteFlg.store(true);
				});
}

void ThreadCreator::Create(const CreateFunc& createFunc, const CompletedFunc& completedFunc)
{
	if (m_Thread.joinable())
	{
		m_Thread.detach();
	}

	m_CompleteFlg.store(false);

	m_Thread = std::thread([=]()
				{	createFunc();
					m_CompleteFlg.store(true);
					completedFunc();
				});
}

bool ThreadCreator::IsLoading()
{
	if (!m_Thread.joinable())
	{
		return false;
	}


	return m_CompleteFlg.load() ? false : true;
}

bool ThreadCreator::IsComplete()
{
	if (!m_Thread.joinable())
	{
		return false;
	}

	return m_CompleteFlg.load() ? true : false;
}
