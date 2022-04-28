#pragma once
#include "Mof.h"

enum tag_SCENENO
{
	SCENE_TITLE,
	SCENE_HOME,
	SCENE_GAME,
	SCENE_RESULT,
};

//��
#define PLAYER_SPEED 0.02f
#define GRAVITY 0.02f
#define GRAVITYMAX 0.05f

//�C���v�b�g�L�[�̖���
const std::string INPUT_KEY_HORIZONTAL = "Horizontal";
const std::string INPUT_KEY_VERTICAL = "Vertical";
const std::string INPUT_KEY_JUMP = "Jump";

//�X�e�[�g�L�[�̖���
const std::string STATE_KEY_MOVE = "Move";