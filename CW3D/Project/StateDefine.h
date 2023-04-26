#pragma once


///////////////////////////////////////////////
///			ステートキーの名称
///////////////////////////////////////////////

//移動ステート
constexpr char* STATE_KEY_MOVE = "Move";
//待機ステート
constexpr char* STATE_KEY_IDLE = "Idle";
//待機モーションステート
constexpr char* STATE_KEY_IDLE_MOTION = "IdleMotion";
//ダッシュステート
constexpr char* STATE_KEY_RUN = "Run";
//ジャンプステート
constexpr char* STATE_KEY_JUMP = "Jump";
//ダッシュジャンプステート
constexpr char* STATE_KEY_RUN_JUMP = "RunJump";
//落下ステート
constexpr char* STATE_KEY_FALL = "Fall";
//ダッシュ落下ステート
constexpr char* STATE_KEY_RUN_FALL = "RunFall";
//着地ステート
constexpr char* STATE_KEY_LANDING = "Landing";
//ダッシュ着地ステート
constexpr char* STATE_KEY_RUN_LANDING = "RunLanding";
//攻撃１ステート
constexpr char* STATE_KEY_ATTACK1 = "Attack1";
//攻撃２ステート
constexpr char* STATE_KEY_ATTACK2 = "Attack2";
//攻撃３ステート
constexpr char* STATE_KEY_ATTACK3 = "Attack3";
//空中攻撃１ステート
constexpr char* STATE_KEY_JUMP_ATTACK1 = "JumpAttack1";
//ダッシュ攻撃１ステート
constexpr char* STATE_KEY_RUN_ATTACK1 = "RunAttack1";
//ダッシュ攻撃２ステート
constexpr char* STATE_KEY_RUN_ATTACK2 = "RunAttack2";
//空中ダッシュ攻撃１ステート
constexpr char* STATE_KEY_RUN_JUMP_ATTACK1 = "RunJumpAttack1";
//空中ダッシュ攻撃２ステート
constexpr char* STATE_KEY_RUN_JUMP_ATTACK2 = "RunJumpAttack2";
//空中ダッシュ攻撃３ステート
constexpr char* STATE_KEY_RUN_JUMP_ATTACK3 = "RunJumpAttack3";
//ダメージステート
constexpr char* STATE_KEY_DAMAGE = "Damage";
//空中ダメージステート
constexpr char* STATE_KEY_FLY_DAMAGE = "FlyDamage";
//ダウンステート
constexpr char* STATE_KEY_DOWN = "Down";
//死亡ステート
constexpr char* STATE_KEY_DEAD = "Dead";
//衝撃波スキルステート
constexpr char* STATE_KEY_SHOCKWAVE_SKILL = "Skill1_1";
//ビームスキルステート
constexpr char* STATE_KEY_BEAM_SKILL = "Skill2_1";
//空中ビームスキルステート
constexpr char* STATE_KEY_JUMP_BEAM_SKILL = "JumpSkill2_1";
//竜巻スキルステート
constexpr char* STATE_KEY_STORM_SKILL = "Skill3_1";
//空中竜巻スキルステート
constexpr char* STATE_KEY_JUMP_STORM_SKILL = "JumpSkill3_1";
//ドロップキックスキルステート
constexpr char* STATE_KEY_DROPKICK_SKILL = "DropKick";
//空中ドロップキックスキルステート
constexpr char* STATE_KEY_JUMP_DROPKICK_SKILL = "JumpDropKickSkill";
//超ジャンプスキルステート
constexpr char* STATE_KEY_FLYHIGH_SKILL = "FlyHighSkill";
//回避ステート
constexpr char* STATE_KEY_ESCAPE = "Escape";
//クリアポーズステート
constexpr char* STATE_KEY_CLEARPOSE = "ClearPose";
//開始ポーズステート
constexpr char* STATE_KEY_STARTPOSE = "StartPose";
//NPC開始ポーズステート
constexpr char* STATE_KEY_NPC_STARTPOSE = "NPCStartPose";
//移動補正ステート
constexpr char* STATE_KEY_MOVECOMPENSATION = "MoveCompensation";

