#include "Messenger.h"

ActionGame::Messenger::Messenger()
{
}

void ActionGame::Messenger::Send(GameMessageType message)
{
	for (auto& recv : receiverLists[message])
	{
		recv->Exection();
	}
}
