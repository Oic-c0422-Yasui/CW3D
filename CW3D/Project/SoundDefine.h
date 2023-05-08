#pragma once
#include "string"

//�T�E���h��
using SoundName = std::string;

/*
* @brief	�T�E���h�^�C�v
*/
enum class SOUND_TYPE
{
	SE,
	BGM
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
