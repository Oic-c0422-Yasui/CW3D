#include "Messenger.h"

ActionGame::Messenger::Messenger()
{
}

void ActionGame::Messenger::Send(GameMessageType message, std::any& value)
{
	for (const auto& recv : receiverLists[message])
	{
		recv->Exec(value);
	}
}
