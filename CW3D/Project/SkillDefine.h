#pragma once
#include <string>



//���݂̃X�L����
#define SKILL_COUNT 4

//�ݒ�ł���ő�X�L����
#define SKILLMAX_COUNT 18

/* �L�[�{�[�h�p�z��@*/
//�X�L���������̍s�̐�
#define SKILL_LEFTLINE_COUNT 1

//�X�L�����^�񒆂̍s�̐�
#define SKILL_CENTERLINE_COUNT 6

//�X�L�����E���̍s�̐�
#define SKILL_RIGHTLINE_COUNT 2

//�X�L�����̗�̐�
#define SKILL_COLUMN_COUNT 2

/* �R���g���[���[�p */
enum ControllerPosCount
{
	Controller_Pos_Up,
	Controller_Pos_Left,
	Controller_Pos_Right,
	Controller_Pos_Down,

	Controller_Pos_Count
};

///////////////////////////////////////////////
///			�X�L���L�[�̖���
///////////////////////////////////////////////

//�X�L���P
const std::string SKILL_KEY_1 = "SkillKey1";
//�X�L���Q
const std::string SKILL_KEY_2 = "SkillKey2";
//�X�L���R
const std::string SKILL_KEY_3 = "SkillKey3";
//�X�L���S
const std::string SKILL_KEY_4 = "SkillKey4";
//�X�L���S
const std::string SKILL_KEY_5 = "SkillKey5";
//����X�L��
const std::string SKILL_KEY_ESCAPE = "EscapeKey";
