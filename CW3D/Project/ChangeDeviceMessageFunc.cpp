#include "ChangeDeviceMessageFunc.h"
#include "RegistMessageServiceDefine.h"
#include "InputManager.h"
#include "DeviceDefine.h"

bool MyUtil::CChangeDeviceMessageFunc::Load(deviceMessageFunc keyBoradFunc, deviceMessageFunc controllerFunc)
{
	//���ݑ��삵�Ă���f�o�C�X�p�̊֐����s
	auto input = InputManagerInstance.GetInput(0);
	switch (input->GetDeviceType())
	{
	case GameDevice::KeyBoardAndMouse:
		keyBoradFunc();
		break;
	case GameDevice::Controller:
		controllerFunc();
		break;
	default:
		break;
	}

	//�f�o�C�X�ύX�ɂ��UI�ύX���b�Z�[�W�o�^
	const auto& message = RegistMessageService::GetService();
	message->Regist(ChangeDevice_KeyBoard,
		keyBoradFunc);
	message->Regist(ChangeDevice_Controller,
		controllerFunc);
    return true;
}
