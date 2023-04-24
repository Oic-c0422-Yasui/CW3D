#include "ChangeDeviceMessageFunc.h"
#include "RegistMessageServiceDefine.h"
#include "InputManager.h"
#include "DeviceDefine.h"

bool MyUtil::CChangeDeviceMessageFunc::Load(deviceMessageFunc keyBoradFunc, deviceMessageFunc controllerFunc)
{
	//現在操作しているデバイス用の関数実行
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

	//デバイス変更によるUI変更メッセージ登録
	const auto& message = RegistMessageService::GetService();
	message->Regist(ChangeDevice_KeyBoard,
		keyBoradFunc);
	message->Regist(ChangeDevice_Controller,
		controllerFunc);
    return true;
}
