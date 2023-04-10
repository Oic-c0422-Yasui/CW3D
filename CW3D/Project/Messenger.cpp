#include "Messenger.h"


Messenger::CMessenger::CMessenger()
	: observeMap_()
{
}
Messenger::CMessenger::~CMessenger()
{
	Delete();
	observeMap_.clear();
}

void Messenger::CMessenger::Send(GameMessageType message)
{
	auto it = observeMap_.find(message);
	assert(it != observeMap_.end());
	it->second.Notify();
}

void Messenger::CMessenger::Regist(GameMessageType message,const std::function<void()>& func)
{
	observeMap_[message].Subscribe(func);
}

void Messenger::CMessenger::Delete(GameMessageType message)
{
	observeMap_[message].Dispose();
}

void Messenger::CMessenger::Delete()
{
	for (auto observer : observeMap_)
	{
		observer.second.Dispose();
	}
}
