#include "Messenger.h"

ActionGame::CMessenger::CMessenger()
{
}

void ActionGame::CMessenger::Send(GameMessageType message)
{
	for (auto& recv : m_ReceiverLists[message])
	{
		recv->Exection();
	}
}
