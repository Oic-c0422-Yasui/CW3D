#pragma once
#include "Common.h"
#include "MessageDefine.h"
#include "IReceiverRegister.h"

namespace ActionGame
{
	/*
	* @brief	���b�Z�[�W�𑗂�N���X�p�C���^�t�F�[�X
	*/
	class IMessenger : public IReceiverRegister
	{
	public:
		virtual ~IMessenger() = default;
		
		/*
		* @brief	���b�Z�[�W�𑗂�
		* @param	message ���b�Z�[�W�̎��
		*/
		virtual void Send(GameMessageType message) = 0;
	};
	using MessengerPtr = std::shared_ptr<IMessenger>;
}


