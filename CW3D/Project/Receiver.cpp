#include "Receiver.h"

ActionGame::Receiver::Receiver(ReceiverFunc param)
	: m_Function(param)
{
}

void ActionGame::Receiver::Exection()
{
	m_Function();
}
