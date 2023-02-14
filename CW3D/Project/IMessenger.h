#pragma once
#include "Common.h"
#include "MessageDefine.h"

namespace ActionGame
{
	/*
	* @brief	メッセージを送るクラス
	*/
	class IMessenger
	{
	public:
		virtual ~IMessenger() = default;

		virtual void Send(GameMessageType message) = 0;
	};
	using MessengerPtr = std::shared_ptr<IMessenger>;
}


