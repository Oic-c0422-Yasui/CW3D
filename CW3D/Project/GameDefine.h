#pragma once
#include "Mof.h"

enum tag_SCENENO
{
	SCENE_TITLE,
	SCENE_HOME,
	SCENE_GAME,
	SCENE_RESULT,
};

enum tag_COLLISIONTYPE
{
	COLLITION_SPHERE,
	COLLITION_AABB,
};

//仮
#define PLAYER_SPEED 0.02f
#define PLAYER_MAXSPEED 0.14f
//プレイヤーの移動速度(0.6倍)
#define PLAYER_WALKSPEED 0.6f
#define GRAVITY 0.02f
#define GRAVITYMAX 0.6f

//インプットキーの名称
const std::string INPUT_KEY_HORIZONTAL = "Horizontal";
const std::string INPUT_KEY_VERTICAL = "Vertical";
const std::string INPUT_KEY_JUMP = "Jump";
const std::string INPUT_KEY_ATTACK = "Attack";
const std::string INPUT_KEY_SKILL1 = "Skill1";

//ステートキーの名称
constexpr char* STATE_KEY_MOVE = "Move";
constexpr char* STATE_KEY_IDLE = "Idle";
constexpr char* STATE_KEY_IDLEMOTION = "IdleMotion";
constexpr char* STATE_KEY_RUN = "Run";
constexpr char* STATE_KEY_ATTACK1 = "Attack1";
constexpr char* STATE_KEY_ATTACK2 = "Attack2";
constexpr char* STATE_KEY_ATTACK3 = "Attack3";
constexpr char* STATE_KEY_RUNATTACK1 = "RunAttack1";
constexpr char* STATE_KEY_DAMAGE = "Damage";
constexpr char* STATE_KEY_SKILL1_1 = "Skill1_1";

//パラメーターキーの名称

const std::string PARAMETER_KEY_KNOCKBACK = "KnockBack";