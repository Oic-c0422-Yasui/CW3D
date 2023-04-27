#include "MessengerUtilities.h"
#include "RegistMessageServiceDefine.h"
#include "InputManager.h"
#include "DeviceDefine.h"

/*///////////////////////////////////////////////////
* @brief	�f�o�C�X�ύX���Ɏ��s����֐������s����
*////////////////////////////////////////////////////

bool MyUtil::CChangeDeviceMessageFunc::Load(const MessageName& name,
											MessageFunc keyBoradFunc,
											MessageFunc controllerFunc)
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
	if (!message) return false;

	message->Regist(ChangeDevice_KeyBoard,
		name, keyBoradFunc);
	message->Regist(ChangeDevice_Controller,
		name, controllerFunc);
    return true;
}

bool MyUtil::CChangeDeviceMessageFunc::Delete(const MessageName& name)
{
	//�f�o�C�X�ύX���b�Z�[�W�폜
	const auto& message = RegistMessageService::GetService();
	if (!message) return false;

	return ( message->Delete(ChangeDevice_KeyBoard, name) &&
			 message->Delete(ChangeDevice_Controller, name) );
}



/*//////////////////////////////////////////////
* @brief	UI�\���E��\�����Ɏ��s����֐���o�^����
*///////////////////////////////////////////////

bool MyUtil::CUIMessageFunc::Load(const MessageName& name, MessageFunc visibleFunc, MessageFunc disableFunc)
{
	//UI�ύX���b�Z�[�W�o�^
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
	//UI�ύX���b�Z�[�W�폜
	const auto& message = RegistMessageService::GetService();
	if (!message) return false;

	return (message->Delete(UI_Visible, name) &&
			message->Delete(UI_Disable, name));
}
