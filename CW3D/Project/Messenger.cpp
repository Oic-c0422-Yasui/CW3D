#include "Messenger.h"


Messenger::CMessenger::CMessenger()
	: observeMap_()
{
}
void Messenger::CMessenger::Send(GameMessageType message) const
{
	auto it = observeMap_.find(message);
	assert(it != observeMap_.end());
	it->second.Notify();
}

void Messenger::CMessenger::Regist(GameMessageType message, const std::function<void>& func)
{
	observeMap_[message].Subscribe(func);
}

void Messenger::CMessenger::Delete(GameMessageType message)
{
	observeMap_[message].clear();
}