#pragma once
#include <functional>

namespace MyUtil
{
	//�f�o�C�X�ύX���Ɏ��s�����֐�
	using deviceMessageFunc = const std::function<void()>&;
	
	/*
	* @brief	�f�o�C�X�ύX���Ɏ��s����֐������s����
	*/
	class CChangeDeviceMessageFunc
	{
	public:
		/*
		* @brief	�ǂݍ���
		* @brief	keyBoradFunc �L�[�{�[�h���Ɏ��s�����֐�
		* @brief	controllerFunc �R���g���[���[���Ɏ��s�����֐�
		*/
		static bool Load(deviceMessageFunc keyBoradFunc,
						deviceMessageFunc controllerFunc);
	};
}

