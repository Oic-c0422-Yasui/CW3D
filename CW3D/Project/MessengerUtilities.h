#pragma once
#include <functional>
#include <string>

namespace MyUtil
{
	//�f�o�C�X�ύX���Ɏ��s�����֐�
	using MessageFunc = std::function<void()>;
	using MessageName = std::string;

	/*
	* @brief	�f�o�C�X�ύX���Ɏ��s����֐������s����
	*/
	class CChangeDeviceMessageFunc
	{
	public:

		/*
		* @brief	�ǂݍ���
		* @param	name			���b�Z�[�W�̖��O
		* @param	keyBoradFunc �L�[�{�[�h���Ɏ��s�����֐�
		* @param	controllerFunc �R���g���[���[���Ɏ��s�����֐�
		*/
		static bool Load(const MessageName& name,
			MessageFunc keyBoradFunc,
			MessageFunc controllerFunc);

		/*
		* @brief	�o�^�����֐����폜����
		* @param	name	���b�Z�[�W�̖��O
		*/
		static bool Delete(const MessageName& name);
	};

	/*
	* @brief	UI�\���E��\�����Ɏ��s����֐���o�^����
	*/
	class CUIMessageFunc
	{
	public:

		/*
		* @brief	�ǂݍ���
		* @param	name			���b�Z�[�W�̖��O
		* @param	visibleFunc UI�\�����Ɏ��s�����֐�
		* @param	disableFunc UI��\�����Ɏ��s�����֐�
		*/
		static bool Load(const MessageName& name,
			MessageFunc visibleFunc,
			MessageFunc disableFunc);

		/*
		* @brief	�o�^�����֐����폜����
		* @param	name	���b�Z�[�W�̖��O
		*/
		static bool Delete(const MessageName& name);
	};
}

