#pragma once
#include "Mof.h"
#include "Utilities.h"
#include	"ServiceLocator.h"

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
#define GRAVITY 0.01f
#define GRAVITYMAX 0.3f
#define PLAYER_JUMPPOWER 0.22f

//インプットキーの名称
const std::string INPUT_KEY_HORIZONTAL = "Horizontal";
const std::string INPUT_KEY_VERTICAL = "Vertical";
const std::string INPUT_KEY_JUMP = "Jump";
const std::string INPUT_KEY_ATTACK = "Attack";
const std::string INPUT_KEY_SKILL1 = "Skill1";
const std::string INPUT_KEY_SKILL2 = "Skill2";
const std::string INPUT_KEY_SKILL3 = "Skill3";
const std::string INPUT_KEY_ESCAPE = "Escape";

//ステートキーの名称
constexpr char* STATE_KEY_MOVE = "Move";
constexpr char* STATE_KEY_IDLE = "Idle";
constexpr char* STATE_KEY_IDLEMOTION = "IdleMotion";
constexpr char* STATE_KEY_RUN = "Run";
constexpr char* STATE_KEY_JUMP = "Jump";
constexpr char* STATE_KEY_RUNJUMP = "RunJump";
constexpr char* STATE_KEY_FALL = "Fall";
constexpr char* STATE_KEY_RUNFALL = "RunFall";
constexpr char* STATE_KEY_LANDING = "Landing";
constexpr char* STATE_KEY_RUNLANDING = "RunLanding";
constexpr char* STATE_KEY_ATTACK1 = "Attack1";
constexpr char* STATE_KEY_ATTACK2 = "Attack2";
constexpr char* STATE_KEY_ATTACK3 = "Attack3";
constexpr char* STATE_KEY_JUMPATTACK1 = "JumpAttack1";
constexpr char* STATE_KEY_RUNATTACK1 = "RunAttack1";
constexpr char* STATE_KEY_RUNJUMPATTACK1 = "RunJumpAttack1";
constexpr char* STATE_KEY_RUNJUMPATTACK2 = "RunJumpAttack2";
constexpr char* STATE_KEY_RUNJUMPATTACK3 = "RunJumpAttack3";
constexpr char* STATE_KEY_DAMAGE = "Damage";
constexpr char* STATE_KEY_FLYDAMAGE = "FlyDamage";
constexpr char* STATE_KEY_DOWN = "Down";
constexpr char* STATE_KEY_DEAD = "Dead";
constexpr char* STATE_KEY_SKILL1_1 = "Skill1_1";
constexpr char* STATE_KEY_SKILL2_1 = "Skill2_1";
constexpr char* STATE_KEY_JUMPSKILL2_1 = "JumpSkill2_1";
constexpr char* STATE_KEY_SKILL3_1 = "Skill3_1";
constexpr char* STATE_KEY_JUMPSKILL3_1 = "JumpSkill3_1";
constexpr char* STATE_KEY_ESCAPE = "Escape";

//パラメーターキーの名称
const std::string PARAMETER_KEY_KNOCKBACK = "KnockBack";
const std::string PARAMETER_KEY_HP = "HP";
const std::string PARAMETER_KEY_MAXHP = "MaxHP";
const std::string PARAMETER_KEY_DAMAGE = "Damage";
const std::string PARAMETER_KEY_ATTACK = "Attack";
const std::string PARAMETER_KEY_ALPHA = "Alpha";
const std::string PARAMETER_KEY_INVINCIBLE = "Invincible";

//スキルキーの名称
const std::string SKILL_KEY_1 = "SkillKey1";
const std::string SKILL_KEY_2 = "SkillKey2";
const std::string SKILL_KEY_3 = "SkillKey3";
const std::string SKILL_KEY_4 = "SkillKey4";
const std::string SKILL_KEY_ESCAPE = "EscapeKey";

//FPS60
constexpr float GameFrameTime = 1.0f / 60.0f;

//初期アーマーレベル
constexpr BYTE DEFAULT_ARMORLEVEL = 1;

enum CHARACTER_TYPE
{
	CHARA_PLAYER,
	CHARA_ENEMY,
	CHARA_OBJECT,
};


/*利用するアニメーションの名前
		char* name;
		アニメ開始時間
		float					startTime;
		アニメ補間時間
		float					tTime;
		アニメ速度
		float					speed;
		アニメループフラグ
		bool					loopFlg;*/
struct AnimParam
{
	//利用するアニメーションの名前
	char*					name;
	//アニメ開始時間
	float					startTime;
	//アニメ速度
	float					speed;
	//アニメ補間時間
	float					tTime;
	//アニメループフラグ
	bool					loopFlg;
};