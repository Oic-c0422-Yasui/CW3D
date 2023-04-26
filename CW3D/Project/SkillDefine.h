#pragma once
#include <string>



//現在のスキル数
#define SKILL_COUNT 4

//設定できる最大スキル数
#define SKILLMAX_COUNT 18

/* キーボード用配列　*/
//スキル欄左側の行の数
#define SKILL_LEFTLINE_COUNT 1

//スキル欄真ん中の行の数
#define SKILL_CENTERLINE_COUNT 6

//スキル欄右側の行の数
#define SKILL_RIGHTLINE_COUNT 2

//スキル欄の列の数
#define SKILL_COLUMN_COUNT 2

/* コントローラー用 */
enum ControllerPosCount
{
	Controller_Pos_Up,
	Controller_Pos_Left,
	Controller_Pos_Right,
	Controller_Pos_Down,

	Controller_Pos_Count
};

///////////////////////////////////////////////
///			スキルキーの名称
///////////////////////////////////////////////

//スキル１
const std::string SKILL_KEY_1 = "SkillKey1";
//スキル２
const std::string SKILL_KEY_2 = "SkillKey2";
//スキル３
const std::string SKILL_KEY_3 = "SkillKey3";
//スキル４
const std::string SKILL_KEY_4 = "SkillKey4";
//スキル４
const std::string SKILL_KEY_5 = "SkillKey5";
//回避スキル
const std::string SKILL_KEY_ESCAPE = "EscapeKey";
