#include "ThreadCreator.h"

ThreadCreator::ThreadCreator()
	: thread_()
	, isComplete_(false)
{
}

ThreadCreator::~ThreadCreator()
{
thread_.join();
}

void ThreadCreator::Create(const CreateFunc& func)
{
	if (thread_.joinable())
	{
		thread_.detach();
	}

	isComplete_.store(false);

	thread_ = std::thread([=]()
				{	func();
					isComplete_.store(true);
				});
}

void ThreadCreator::Create(const CreateFunc& createFunc, const CompletedFunc& completedFunc)
{
	if (thread_.joinable())
	{
		thread_.detach();
	}

	isComplete_.store(false);

	thread_ = std::thread([=]()
				{	createFunc();
					isComplete_.store(true);
					completedFunc();
				});
}

bool ThreadCreator::IsLoading()
{
	if (!thread_.joinable())
	{
		return false;
	}


	return isComplete_.load() ? false : true;
}

bool ThreadCreator::IsComplete()
{
	if (!thread_.joinable())
	{
		return false;
	}

	return isComplete_.load() ? true : false;
}
