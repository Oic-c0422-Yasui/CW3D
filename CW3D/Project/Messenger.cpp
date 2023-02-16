#include "Messenger.h"

ActionGame::IObservable<void>& Messenger::CMessenger::GetSubscribe(GameMessageType message)
{
	return m_ObserveMap[message];
}

Messenger::CMessenger::CMessenger()
	: m_ObserveMap()
{
}

void Messenger::CMessenger::Regist(GameMessageType message, const std::function<void>& func)
{
	GetSubscribe(message).Subscribe([&]() { ; });
}

void Messenger::CMessenger::Send(GameMessageType message)
{
	auto it = m_ObserveMap.find(message);
	assert(it != observeMap.end());
	it->second.Notify();
}
