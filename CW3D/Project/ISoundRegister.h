#pragma once
#include "Sound.h"

class __declspec(novtable) ISoundRegister
{
public:
	virtual ~ISoundRegister() = default;
	/*
	* @brief	�T�E���h��ǉ�����
	* @param	sound	�o�^����T�E���h�̃|�C���^
	* @param	tag		�o�^����Ă���T�E���h�̃^�O
	* @param	name	�o�^����Ă���T�E���h�̖��O
	*/
	virtual void AddSound(const MyClass::SoundPtr& sound, SCENE_SOUND_TAG tag,const SoundName& name) = 0;
	/*
	* @brief	�T�E���h�����ׂč폜����
	*/
	virtual bool DeleteSound() = 0;
	/*
	* @brief	�^�O���̃T�E���h���폜����
	* @param	tag		�o�^����Ă���T�E���h�̃^�O
	*/
	virtual bool DeleteSound(SCENE_SOUND_TAG tag) = 0;
	/*
	* @brief	�^�O���̃T�E���h���폜����
	* @param	tag		�o�^����Ă���T�E���h�̃^�O
	* @param	name	�o�^����Ă���T�E���h�̖��O
	*/
	virtual bool DeleteSound(SCENE_SOUND_TAG tag, const SoundName& name) = 0;
};
