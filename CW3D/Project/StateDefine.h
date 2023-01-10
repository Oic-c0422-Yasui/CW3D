#pragma once


///////////////////////////////////////////////
///			ステートキーの名称
///////////////////////////////////////////////

//移動ステート
constexpr char* STATE_KEY_MOVE = "Move";
//待機ステート
constexpr char* STATE_KEY_IDLE = "Idle";
//待機モーションステート
constexpr char* STATE_KEY_IDLEMOTION = "IdleMotion";
//ダッシュステート
constexpr char* STATE_KEY_RUN = "Run";
//ジャンプステート
constexpr char* STATE_KEY_JUMP = "Jump";
//ダッシュジャンプステート
constexpr char* STATE_KEY_RUNJUMP = "RunJump";
//落下ステート
constexpr char* STATE_KEY_FALL = "Fall";
//ダッシュ落下ステート
constexpr char* STATE_KEY_RUNFALL = "RunFall";
//着地ステート
constexpr char* STATE_KEY_LANDING = "Landing";
//ダッシュ着地ステート
constexpr char* STATE_KEY_RUNLANDING = "RunLanding";
//攻撃１ステート
constexpr char* STATE_KEY_ATTACK1 = "Attack1";
//攻撃２ステート
constexpr char* STATE_KEY_ATTACK2 = "Attack2";
//攻撃３ステート
constexpr char* STATE_KEY_ATTACK3 = "Attack3";
//空中攻撃１ステート
constexpr char* STATE_KEY_JUMPATTACK1 = "JumpAttack1";
//ダッシュ攻撃１ステート
constexpr char* STATE_KEY_RUNATTACK1 = "RunAttack1";
//空中ダッシュ攻撃１ステート
constexpr char* STATE_KEY_RUNJUMPATTACK1 = "RunJumpAttack1";
//空中ダッシュ攻撃２ステート
constexpr char* STATE_KEY_RUNJUMPATTACK2 = "RunJumpAttack2";
//空中ダッシュ攻撃３ステート
constexpr char* STATE_KEY_RUNJUMPATTACK3 = "RunJumpAttack3";
//ダメージステート
constexpr char* STATE_KEY_DAMAGE = "Damage";
//空中ダメージステート
constexpr char* STATE_KEY_FLYDAMAGE = "FlyDamage";
//ダウンステート
constexpr char* STATE_KEY_DOWN = "Down";
//死亡ステート
constexpr char* STATE_KEY_DEAD = "Dead";
//衝撃波スキルステート
constexpr char* STATE_KEY_SHOCKWAVESKILL = "Skill1_1";
//ビームスキルステート
constexpr char* STATE_KEY_BEAMSKILL = "Skill2_1";
//空中ビームスキルステート
constexpr char* STATE_KEY_JUMPBEAMSKILL = "JumpSkill2_1";
//竜巻スキルステート
constexpr char* STATE_KEY_STORMSKILL = "Skill3_1";
//空中竜巻スキルステート
constexpr char* STATE_KEY_JUMPSTORMSKILL = "JumpSkill3_1";
//ドロップキックスキルステート
constexpr char* STATE_KEY_DROPKICKSKILL = "DropKick";
//空中ドロップキックスキルステート
constexpr char* STATE_KEY_JUMPDROPKICKSKILL = "JumpDropKickSkill";
//回避ステート
constexpr char* STATE_KEY_ESCAPE = "Escape";
//クリアポーズステート
constexpr char* STATE_KEY_CLEARPOSE = "ClearPose";
//開始ポーズステート
constexpr char* STATE_KEY_STARTPOSE = "StartPose";
//NPC開始ポーズステート
constexpr char* STATE_KEY_NPCSTARTPOSE = "NPCStartPose";
