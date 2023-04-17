#include "OperateDeviceState.h"
#include "SendMessageServiceDefine.h"

COperateDeviceState::COperateDeviceState()
	: currentDevice_(GameDevice::KeyBoardAndMouse)
	, prevDevice_(GameDevice::KeyBoardAndMouse)
{
}



void COperateDeviceState::SendDeviceMessage()
{

	//デバイスが変更されてない場合はメッセージを送信しない
	if (currentDevice_ == prevDevice_)
	{
		return;
	}
	prevDevice_ = currentDevice_;


	//操作デバイスに合ったメッセージに変更
	auto messageType = GameMessageType::ChangeDevice_KeyBoard;
	switch (currentDevice_)
	{
	case GameDevice::KeyBoardAndMouse:
		messageType = GameMessageType::ChangeDevice_KeyBoard;
		break;
	case GameDevice::Controller:
		messageType = GameMessageType::ChangeDevice_Controller;
		break;
	default:
		break;
	}

	//メッセージ送信
	SendMessageService::GetService()->Send(messageType);
}

void COperateDeviceState::ChangeDevice(GameDevice device) noexcept
{
	//デバイスが変わっていない場合は何もしない
	if (currentDevice_ == device)
	{
		return;
	}

	prevDevice_ = currentDevice_;
	currentDevice_ = device;
}

GameDevice COperateDeviceState::GetDeviceType() const noexcept
{
	return currentDevice_;
}


