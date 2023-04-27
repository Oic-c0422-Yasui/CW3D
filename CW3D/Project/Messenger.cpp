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

bool Messenger::CMessenger::Send(GameMessageType message)
{
	auto it = observeMap_.find(message);
	if (it != observeMap_.end())
	{
		//‘—M
		for (auto message : it->second)
		{
			message.second.Notify();
		}
		return true;
	}
	return false;
}

void Messenger::CMessenger::Regist(GameMessageType type, const MessageName& name, const MessageFuncPtr& func)
{
	observeMap_[type][name].Subscribe(func);
}

Messenger::MessageFuncPtr Messenger::CMessenger::Regist(GameMessageType type, const MessageName& name, const MessageFunc& func)
{
	return observeMap_[type][name].Subscribe(func);
}

bool Messenger::CMessenger::Delete(GameMessageType type, const MessageName& name)
{
	auto& map = observeMap_[type];
	auto it = map.find(name);
	if (it != map.end())
	{
		it->second.Dispose();
		return true;
	}
	return false;
}

bool Messenger::CMessenger::Delete()
{
	for (auto map : observeMap_)
	{
		for (auto observer : map.second)
		{
			observer.second.Dispose();
		}
	}
	return true;
}
