#pragma once
#include "Mof.h"
#include "Utilities.h"
#include	"ServiceLocator.h"

//�^�X�N�̗D�揇�ʁi�������Ⴂ�قǗD�悳���j
enum Task_Priority
{
	TASK_EVENT,		//�C�x���g�^�X�N
	TASK_MAIN1,		//���C���^�X�N�P
	TASK_MAIN2,		//���C���^�X�N�Q
	TASK_MAIN3,		//���C���^�X�N�R
	TASK_COLLISION,	//�Փ˃^�X�N
};

//�V�[���ԍ�
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

//��
#define PLAYER_SPEED 0.02f
#define PLAYER_MAXSPEED 0.14f
//�v���C���[�̈ړ����x(0.6�{)
#define PLAYER_WALKSPEED 0.6f
#define GRAVITY 0.01f
#define GRAVITYMAX 0.3f
#define PLAYER_JUMPPOWER 0.22f

//�C���v�b�g�L�[�̖���
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

//�X�e�[�g�L�[�̖���
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

//�p�����[�^�[�L�[�̖���
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

//�X�L���L�[�̖���
const std::string SKILL_KEY_1 = "SkillKey1";
const std::string SKILL_KEY_2 = "SkillKey2";
const std::string SKILL_KEY_3 = "SkillKey3";
const std::string SKILL_KEY_DROPKICK = "SkillKey4";
const std::string SKILL_KEY_ESCAPE = "EscapeKey";

//���݂̃X�L����
#define SKILL_COUNT 4

//�ݒ�ł���ő�X�L����
#define SKILLMAX_COUNT 18

//�X�L���������̍s�̐�
#define SKILL_LEFTLINE_COUNT 1

//�X�L�����^�񒆂̍s�̐�
#define SKILL_CENTERLINE_COUNT 6

//�X�L�����E���̍s�̐�
#define SKILL_RIGHTLINE_COUNT 2

//�X�L�����̗�̐�
#define SKILL_COLUMN_COUNT 2


//FPS60
constexpr float GameFrameTime = 1.0f / 60.0f;

//�����A�[�}�[���x��
constexpr BYTE DEFAULT_ARMORLEVEL = 1;

//�L�����^�C�v
enum CHARACTER_TYPE
{
	CHARA_PLAYER,
	CHARA_ENEMY,
	CHARA_OBJECT,

	CHARA_COUNT,
};





/* �A�j���[�V�����p�����[�^
* 
*	name		�A�j���[�V�����̖��O
* 
*	startTime	�A�j���[�V�����J�n����
* 
*	speed		�A�j���[�V�������x
* 
*	tTime		�A�j���[�V������Ԏ���
* 
*	loopFlg		�A�j���[�V�������[�v�t���O
*/
struct AnimParam
{
	//���p����A�j���[�V�����̖��O
	char*					name;
	//�A�j���[�V�����J�n����
	float					startTime;
	//�A�j���[�V�������x
	float					speed;
	//�A�j���[�V������Ԏ���
	float					tTime;
	//�A�j���[�V�������[�v�t���O
	bool					loopFlg;
};