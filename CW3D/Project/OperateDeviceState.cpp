#include "OperateDeviceState.h"
#include "SendMessageServiceDefine.h"

COperateDeviceState::COperateDeviceState()
	: currentDevice_(GameDevice::KeyBoardAndMouse)
	, prevDevice_(GameDevice::KeyBoardAndMouse)
{
}



void COperateDeviceState::SendDeviceMessage()
{

	//�f�o�C�X���ύX����ĂȂ��ꍇ�̓��b�Z�[�W�𑗐M���Ȃ�
	if (currentDevice_ == prevDevice_)
	{
		return;
	}
	prevDevice_ = currentDevice_;


	//����f�o�C�X�ɍ��������b�Z�[�W�ɕύX
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

	//���b�Z�[�W���M
	SendMessageService::GetService()->Send(messageType);
}

void COperateDeviceState::ChangeDevice(GameDevice device) noexcept
{
	//�f�o�C�X���ς���Ă��Ȃ��ꍇ�͉������Ȃ�
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


