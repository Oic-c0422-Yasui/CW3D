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
#define PLAYER_MAXSPEED 0.14f
//�v���C���[�̈ړ����x(0.6�{)
#define PLAYER_WALKSPEED 0.6f
#define GRAVITY 0.02f
#define GRAVITYMAX 0.6f

//�C���v�b�g�L�[�̖���
const std::string INPUT_KEY_HORIZONTAL = "Horizontal";
const std::string INPUT_KEY_VERTICAL = "Vertical";
const std::string INPUT_KEY_JUMP = "Jump";
const std::string INPUT_KEY_ATTACK = "Attack";

//�X�e�[�g�L�[�̖���
constexpr char* STATE_KEY_MOVE = "Move";
constexpr char* STATE_KEY_IDLE = "Idle";
constexpr char* STATE_KEY_IDLEMOTION = "IdleMotion";
constexpr char* STATE_KEY_RUN = "Run";
constexpr char* STATE_KEY_ATTACK1 = "Attack1";
constexpr char* STATE_KEY_ATTACK2 = "Attack2";