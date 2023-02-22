#include "Messenger.h"


Messenger::CMessenger::CMessenger()
	: m_ObserveMap()
{
}
void Messenger::CMessenger::Send(GameMessageType message) const
{
	auto it = m_ObserveMap.find(message);
	assert(it != m_ObserveMap.end());
	it->second.Notify();
}

void Messenger::CMessenger::Regist(GameMessageType message, const std::function<void>& func)
{
	m_ObserveMap[message].Subscribe([&](int a) {10; });
}

void Messenger::CMessenger::Delete(GameMessageType message)
{
	m_ReceiverLists[message].clear();
}