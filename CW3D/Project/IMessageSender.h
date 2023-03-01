#pragma once
#include "MessageDefine.h"

namespace Messenger
{
	/*
	* @brief	メッセージを送るインタフェース
	*/
	class __declspec(novtable) ISender
	{
	public:
		virtual ~ISender() = default;
		/*
		* @brief	メッセージを送る
		* @param	message メッセージの種類
		*/
		virtual void Send(GameMessageType message) = 0;
	};
}