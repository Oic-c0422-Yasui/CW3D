#pragma once
#include <memory>
#include "IMessageRegister.h"
#include "IMessageSender.h"

namespace Messenger
{
	/*
	* @brief	���b�Z�[�W���Ǘ�����p�C���^�t�F�[�X
	*/
	class IMessenger : public IRegister, public ISender
 	{
	public:
		virtual ~IMessenger() = default;
		
	};
	using MessengerPtr = std::shared_ptr<IMessenger>;
}


