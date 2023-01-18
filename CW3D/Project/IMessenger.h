#pragma once
#include "Common.h"
#include "MessageDefine.h"

namespace ActionGame
{

	class IMessenger
	{
	public:
		virtual ~IMessenger() = default;

		virtual void Send(GameMessageType message, std::any& value) = 0;
	};
	using MessengerPtr = std::shared_ptr<IMessenger>;
}


