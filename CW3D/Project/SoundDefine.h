#pragma once
#include "string"

//�T�E���h��
using SoundName = std::string;

/*
* @brief	�T�E���h�^�C�v
*/
enum SOUND_TYPE
{
	SOUND_SE,
	SOUND_BGM,

	SOUND_MASTER,	//�S�̂̃T�E���h
	SOUND_COUNT,	//�^�C�v�̐�
};

/*
* @brief	�T�E���h����
*/
enum class SOUND_EFFECT_TYPE
{
	NONE,	//�Ȃ�
	FADE,	//�t�F�[�h
};
