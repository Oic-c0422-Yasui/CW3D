#pragma once
#include "Mof.h"
#include "Utilities.h"
#include	"ServiceLocator.h"

//タスクの優先順位（数字が低いほど優先される）
enum Task_Priority
{
	TASK_EVENT,		//イベントタスク
	TASK_MAIN1,		//メインタスク１
	TASK_MAIN2,		//メインタスク２
	TASK_MAIN3,		//メインタスク３
	TASK_COLLISION,	//衝突タスク
};

//シーン番号
enum tag_SCENENO
{
	SCENE_TITLE,
	SCENE_HOME,
	SCENE_GAME,
	SCENE_RESULT,
};

enum tag_COLLISIONTYPE
{
	COLLISION_SPHERE,
	COLLISION_AABB,
	COLLISION_OBB,
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
const std::string INPUT_KEY_ENTER = "Attack";
const std::string INPUT_KEY_SKILL1 = "Skill1";
const std::string INPUT_KEY_SKILL2 = "Skill2";
const std::string INPUT_KEY_SKILL3 = "Skill3";
const std::string INPUT_KEY_SKILL_DROPKICK = "Skill_DropKick";
const std::string INPUT_KEY_ESCAPE = "Escape";
const std::string INPUT_KEY_RETRY = "Retry";

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
constexpr char* STATE_KEY_SHOCKWAVESKILL = "Skill1_1";
constexpr char* STATE_KEY_BEAMSKILL = "Skill2_1";
constexpr char* STATE_KEY_JUMPBEAMSKILL = "JumpSkill2_1";
constexpr char* STATE_KEY_STORMSKILL = "Skill3_1";
constexpr char* STATE_KEY_JUMPSTORMSKILL = "JumpSkill3_1";
constexpr char* STATE_KEY_DROPKICKSKILL = "DropKick";
constexpr char* STATE_KEY_JUMPDROPKICKSKILL = "JumpDropKickSkill";
constexpr char* STATE_KEY_ESCAPE = "Escape";
constexpr char* STATE_KEY_CLEARPOSE = "ClearPose";

//パラメーターキーの名称
const std::string PARAMETER_KEY_KNOCKBACK = "KnockBack";
const std::string PARAMETER_KEY_HP = "HP";
const std::string PARAMETER_KEY_MAXHP = "MaxHP";
const std::string PARAMETER_KEY_ULTGAUGE = "ULTGauge";
const std::string PARAMETER_KEY_MAXULTGAUGE = "MaxULTGauge";
const std::string PARAMETER_KEY_DAMAGE = "Damage";
const std::string PARAMETER_KEY_ATTACK = "Attack";
const std::string PARAMETER_KEY_ALPHA = "Alpha";
const std::string PARAMETER_KEY_INVINCIBLE = "Invincible";
const std::string PARAMETER_KEY_ESCAPE = "Escape";

//スキルキーの名称
const std::string SKILL_KEY_1 = "SkillKey1";
const std::string SKILL_KEY_2 = "SkillKey2";
const std::string SKILL_KEY_3 = "SkillKey3";
const std::string SKILL_KEY_DROPKICK = "SkillKey4";
const std::string SKILL_KEY_ESCAPE = "EscapeKey";

//現在のスキル数
#define SKILL_COUNT 4

//設定できる最大スキル数
#define SKILLMAX_COUNT 18

//スキル欄左側の行の数
#define SKILL_LEFTLINE_COUNT 1

//スキル欄真ん中の行の数
#define SKILL_CENTERLINE_COUNT 6

//スキル欄右側の行の数
#define SKILL_RIGHTLINE_COUNT 2

//スキル欄の列の数
#define SKILL_COLUMN_COUNT 2


//FPS60
constexpr float GameFrameTime = 1.0f / 60.0f;

//初期アーマーレベル
constexpr BYTE DEFAULT_ARMORLEVEL = 1;

//キャラタイプ
enum CHARACTER_TYPE
{
	CHARA_PLAYER,
	CHARA_ENEMY,
	CHARA_OBJECT,

	CHARA_COUNT,
};





/* アニメーションパラメータ
* 
*	name		アニメーションの名前
* 
*	startTime	アニメーション開始時間
* 
*	speed		アニメーション速度
* 
*	tTime		アニメーション補間時間
* 
*	loopFlg		アニメーションループフラグ
*/
struct AnimParam
{
	//利用するアニメーションの名前
	char*					name;
	//アニメーション開始時間
	float					startTime;
	//アニメーション速度
	float					speed;
	//アニメーション補間時間
	float					tTime;
	//アニメーションループフラグ
	bool					loopFlg;
};