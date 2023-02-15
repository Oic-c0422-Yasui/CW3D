#pragma once
#include "Common.h"
#include "MessageDefine.h"
#include "IReceiverRegister.h"

namespace ActionGame
{
	/*
	* @brief	メッセージを送るクラス用インタフェース
	*/
	class IMessenger : public IReceiverRegister
	{
	public:
		virtual ~IMessenger() = default;
		
		/*
		* @brief	メッセージを送る
		* @param	message メッセージの種類
		*/
		virtual void Send(GameMessageType message) = 0;
	};
	using MessengerPtr = std::shared_ptr<IMessenger>;
}


