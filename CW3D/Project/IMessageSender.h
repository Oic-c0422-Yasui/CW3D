#pragma once
#include "MessageDefine.h"

namespace Messenger
{
	/*
	* @brief	���b�Z�[�W�𑗂�C���^�t�F�[�X
	*/
	class __declspec(novtable) ISender
	{
	public:
		virtual ~ISender() = default;
		/*
		* @brief	���b�Z�[�W�𑗂�
		* @param	message ���b�Z�[�W�̎��
		*/
		virtual bool Send(GameMessageType message) = 0;
	};
}