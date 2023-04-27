#pragma once
#include <memory>
#include "IMessageRegister.h"
#include "IMessageSender.h"

namespace Messenger
{
	/*
	* @brief	メッセージを管理する用インタフェース
	*/
	class IMessenger : public IRegister, public ISender
 	{
	public:
		virtual ~IMessenger() = default;
		
	};
	using MessengerPtr = std::shared_ptr<IMessenger>;
}


