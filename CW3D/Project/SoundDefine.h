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
	SOUND_MASTER,

	SOUND_COUNT,
};

/*
* @brief	�T�E���h����
*/
enum class SOUND_EFFECT_TYPE
{
	NONE,	//�Ȃ�
	FADE,	//�t�F�[�h
};

/*
* @brief	�V�[���ʃT�E���h�^�O
*/
enum class SCENE_SOUND_TAG
{
	ALWAYS, //�����Ǝg��
	TITLE,	//�^�C�g���V�[��
	HOME,	//���_�V�[��
	BATTLE	//�o�g���V�[��
};
