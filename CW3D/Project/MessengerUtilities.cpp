#include "MessengerUtilities.h"
#include "RegistMessageServiceDefine.h"
#include "InputManager.h"
#include "DeviceDefine.h"

/*///////////////////////////////////////////////////
* @brief	デバイス変更時に実行する関数を実行する
*////////////////////////////////////////////////////

bool MyUtil::CChangeDeviceMessageFunc::Load(const MessageName& name,
											MessageFunc keyBoradFunc,
											MessageFunc controllerFunc)
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
	if (!message) return false;

	message->Regist(ChangeDevice_KeyBoard,
		name, keyBoradFunc);
	message->Regist(ChangeDevice_Controller,
		name, controllerFunc);
    return true;
}

bool MyUtil::CChangeDeviceMessageFunc::Delete(const MessageName& name)
{
	//デバイス変更メッセージ削除
	const auto& message = RegistMessageService::GetService();
	if (!message) return false;

	return ( message->Delete(ChangeDevice_KeyBoard, name) &&
			 message->Delete(ChangeDevice_Controller, name) );
}



/*//////////////////////////////////////////////
* @brief	UI表示・非表示時に実行する関数を登録する
*///////////////////////////////////////////////

bool MyUtil::CUIMessageFunc::Load(const MessageName& name, MessageFunc visibleFunc, MessageFunc disableFunc)
{
	//UI変更メッセージ登録
	const auto& message = RegistMessageService::GetService();
	if (!message) return false;

	message->Regist(UI_Visible,
		name, visibleFunc);
	message->Regist(UI_Disable,
		name, disableFunc);
	return true;
}

bool MyUtil::CUIMessageFunc::Delete(const MessageName& name)
{
	//UI変更メッセージ削除
	const auto& message = RegistMessageService::GetService();
	if (!message) return false;

	return (message->Delete(UI_Visible, name) &&
			message->Delete(UI_Disable, name));
}
