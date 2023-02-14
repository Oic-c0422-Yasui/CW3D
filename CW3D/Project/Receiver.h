#pragma once
#include "IReceiver.h"

namespace ActionGame
{
	class Receiver : public IReceiver
	{
	private:
		ReceiverFunc m_Function;
	public:
		Receiver(ReceiverFunc param);
		void Exection() override;
	};
}




