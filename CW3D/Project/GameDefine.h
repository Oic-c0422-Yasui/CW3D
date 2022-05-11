#pragma once
#include "Mof.h"

enum tag_SCENENO
{
	SCENE_TITLE,
	SCENE_HOME,
	SCENE_GAME,
	SCENE_RESULT,
};

//仮
#define PLAYER_SPEED 0.02f
#define PLAYER_MAXSPEED 0.14f
#define PLAYER_WALKSPEED 0.6
#define GRAVITY 0.02f
#define GRAVITYMAX 0.05f

//インプットキーの名称
const std::string INPUT_KEY_HORIZONTAL = "Horizontal";
const std::string INPUT_KEY_VERTICAL = "Vertical";
const std::string INPUT_KEY_JUMP = "Jump";
const std::string INPUT_KEY_ATTACK = "Attack";

//ステートキーの名称
const std::string STATE_KEY_MOVE = "Move";
const std::string STATE_KEY_IDLE = "Idle";
const std::string STATE_KEY_IDLEMOTION = "IdleMotion";
const std::string STATE_KEY_RUN = "Run";
const std::string STATE_KEY_ATTACK1 = "Attack1";
const std::string STATE_KEY_ATTACK2 = "Attack2";