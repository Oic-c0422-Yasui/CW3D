#pragma once

#include	"IActionCreator.h"
#include	"IdleAction.h"
#include	"MoveAction.h"
#include	"JumpAction.h"
#include	"FallAction.h"
#include	"LandingAction.h"
#include	"Attack1Action.h"
#include	"Attack2Action.h"
#include	"Attack3Action.h"


#include	"RunAction.h"
#include	"IdleMotionAction.h"

#include	"RunAttack1Action.h"
#include	"Skill1_1Action.h"

#include	"RunJumpAction.h"
#include	"RunFallAction.h"
#include	"RunLandingAction.h"
#include	"RunJumpAttack1Action.h"
#include	"RunJumpAttack2Action.h"
#include	"RunJumpAttack3Action.h"
#include	"JumpAttack1Action.h"
#include	"Skill2_1Action.h"
#include	"JumpSkill2_1Action.h"
#include	"Skill3_1Action.h"
#include	"JumpSkill3_1Action.h"
#include	"FlyDamageAction.h"
#include	"DownAction.h"

#include	"DamageAction.h"
#include	"DeadAction.h"
#include	"EscapeAction.h"
#include	"ClearPoseAction.h"
#include	"DropKickSkillAction.h"


namespace Sample {
	/**
	 * @brief		アクション生成インターフェイス
	 */
	class PlayerActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~PlayerActionCreator() = default;


		/*
		利用するアニメーションの名前
		char*					name;
		アニメ開始時間
		float					startTime;
		アニメ速度
		float					speed;
		アニメ補間時間
		float					tTime;
		アニメループフラグ
		bool					loopFlg;
		*/

		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr& actor) override {
			//待機
			actor->AddAction(Action::Create<IdleAction>(
				IdleAction::Parameter{
					AnimParam{
						STATE_KEY_IDLE,
						0.0f,
						1.0f,
						0.25f,
						true
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f,PLAYER_SPEED * 0.3f),
					Vector3(PLAYER_SPEED, 1.0f,PLAYER_SPEED)
				}));
			//待機モーション
			actor->AddAction(Action::Create<IdleMotionAction>(
				IdleMotionAction::Parameter{
					AnimParam{
						STATE_KEY_IDLEMOTION,
						0.0f,
						1.0f,
						0.3f,
						false
					},
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED)
				}));
			//移動
			actor->AddAction(Action::Create<MoveAction>(
				MoveAction::Parameter{
					AnimParam{
						STATE_KEY_MOVE,
						0.0f,
						1.0f,
						0.1f,
						true
					},
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					GRAVITYMAX,
				}));
			//ダッシュ
			actor->AddAction(Action::Create<RunAction>(
				RunAction::Parameter{
					AnimParam{
						STATE_KEY_RUN,
						0.0f,
						1.0f,
						0.12f,
						true
					},
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
					Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
					GRAVITYMAX,
				}));
			//ジャンプ
			actor->AddAction(Action::Create<JumpAction>(
				JumpAction::Parameter{
					AnimParam{
						STATE_KEY_JUMP,
						0.3f,
						2.0f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					GRAVITY,
					GRAVITYMAX,
					PLAYER_JUMPPOWER,
				}));
			//ダッシュジャンプ
			actor->AddAction(Action::Create<RunJumpAction>(
				RunJumpAction::Parameter{
					AnimParam{
						STATE_KEY_JUMP,
						0.3f,
						2.0f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
					Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
					GRAVITY,
					GRAVITYMAX,
					PLAYER_JUMPPOWER,
				}));
			//落下
			actor->AddAction(Action::Create<FallAction>(
				FallAction::Parameter{
					AnimParam{
						STATE_KEY_JUMP,
						0.83f,
						1.0f,
						0.2f,
						false
					},
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					GRAVITY,
					GRAVITYMAX,
				}));
			//ダッシュ落下
			actor->AddAction(Action::Create<RunFallAction>(
				RunFallAction::Parameter{
					AnimParam{
						STATE_KEY_JUMP,
						0.83f,
						1.0f,
						0.2f,
						false
					},
					Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
					Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
					GRAVITY,
					GRAVITYMAX,
				}));
			//着地
			actor->AddAction(Action::Create<LandingAction>(
				LandingAction::Parameter{
					AnimParam{
						STATE_KEY_LANDING,
						0.0f,
						1.0f,
						0.1f,
						false
					}
				}));
			//ジャンプ着地
			actor->AddAction(Action::Create<RunLandingAction>(
				RunLandingAction::Parameter{
					AnimParam{
						STATE_KEY_LANDING,
						0.0f,
						1.0f,
						0.1f,
						false
					}
				}));

			//攻撃１
			actor->AddAction(Action::Create<Attack1Action>(
				Attack1Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK1,
						0.0f,
						1.5f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
					Vector3(0.2f, 1.0f, 1.0f),
				}));

			//攻撃２
			actor->AddAction(Action::Create<Attack2Action>(
				Attack2Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK2,
						0.0f,
						1.3f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
					Vector3(0.1f, 0.0f, 0.0f),
				}));

			//攻撃３
			actor->AddAction(Action::Create<Attack3Action>(
				Attack3Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK3,
						0.0f,
						1.3f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
					Vector3(0.05f, 0.0f, 0.0f),
					Vector3(0.1f, 0.0f, 0.0f),
				}));

			//ダッシュ攻撃１
			actor->AddAction(Action::Create<RunAttack1Action>(
				RunAttack1Action::Parameter{
					AnimParam{
						STATE_KEY_RUNATTACK1,
						0.0f,
						1.2f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
				}));

			//ジャンプ攻撃１
			actor->AddAction(Action::Create<JumpAttack1Action>(
				JumpAttack1Action::Parameter{
					AnimParam{
						STATE_KEY_RUNATTACK1,
						0.0f,
						1.2f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
					GRAVITY,
				}));

			//ダッシュジャンプ攻撃１
			actor->AddAction(Action::Create<RunJumpAttack1Action>(
				RunJumpAttack1Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK1,
						0.0f,
						1.7f,
						0.1f,
						false
					},
					Vector3(0.25f, 0.0f, 0.0f),
					PLAYER_JUMPPOWER * 0.4f,
					GRAVITY * 0.7f,
					GRAVITY,
				}));
			//ダッシュジャンプ攻撃２
			actor->AddAction(Action::Create<RunJumpAttack2Action>(
				RunJumpAttack2Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK2,
						0.0f,
						1.5f,
						0.1f,
						false
					},
					Vector3(0.25f, 0.0f,0.0f),
					PLAYER_JUMPPOWER * 0.4f,
					GRAVITY * 0.7f,
					GRAVITY,
				}));
			//ダッシュジャンプ攻撃３
			actor->AddAction(Action::Create<RunJumpAttack3Action>(
				RunJumpAttack3Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK3,
						0.0f,
						1.5f,
						0.1f,
						false
					},
					Vector3(0.25f, 0.0f, 0.0f),
					PLAYER_JUMPPOWER * 0.4f,
					GRAVITY * 0.7f,
					GRAVITY,
				}));

			//ダメージ
			actor->AddAction(Action::Create<DamageAction>(
				DamageAction::Parameter{
					AnimParam{
						STATE_KEY_DAMAGE,
						0.0f,
						1.5f,
						0.1f,
						false
					},
					Vector3(0.05f, 1.0f, 0.05f),
					GRAVITY,
					GRAVITYMAX,
				}));
			//空中ダメージ
			actor->AddAction(Action::Create<FlyDamageAction>(
				FlyDamageAction::Parameter{
					AnimParam{
						STATE_KEY_FLYDAMAGE,
						0.0f,
						1.2f,
						0.1f,
						false
					},
					Vector3(0.05f, 1.0f, 0.05f),
					GRAVITY,
					GRAVITYMAX * 0.4f,
				}));

			//ダウン
			actor->AddAction(Action::Create<DownAction>(
				DownAction::Parameter{
					AnimParam{
						STATE_KEY_DOWN,
						0.0f,
						1.2f,
						0.1f,
						false
					},
					Vector3(0.05f, 1.0f, 0.05f),
				}));

			//死亡
			actor->AddAction(Action::Create<DeadAction>(
				DeadAction::Parameter{
					AnimParam{
						STATE_KEY_DOWN,
						0.0f,
						1.2f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
					2.0f,
				}));

			//スキル
			actor->AddAction(Action::Create<Skill1_1Action>(
				Skill1_1Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK1,
						0.0f,
						0.7f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
				}));

			//スキル
			actor->AddAction(Action::Create<Skill2_1Action>(
				Skill2_1Action::Parameter{
					AnimParam{
						STATE_KEY_SKILL2_1,
						0.7f,
						2.0f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
				}));
			//スキル
			actor->AddAction(Action::Create<Skill3_1Action>(
				Skill3_1Action::Parameter{
					AnimParam{
						STATE_KEY_SKILL3_1,
						0.0f,
						0.6f,
						0.1f,
						true
					},
					Vector3(PLAYER_MAXSPEED* PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED* PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED* PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED* PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED* PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED* PLAYER_WALKSPEED),
				}));
			//空中スキル
			actor->AddAction(Action::Create<JumpSkill2_1Action>(
				JumpSkill2_1Action::Parameter{
					AnimParam{
						STATE_KEY_SKILL2_1,
						0.7f,
						2.0f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
				}));
			//空中スキル
			actor->AddAction(Action::Create<JumpSkill3_1Action>(
				JumpSkill3_1Action::Parameter{
					AnimParam{
						STATE_KEY_SKILL3_1,
						0.0f,
						0.6f,
						0.1f,
						true
					},
					Vector3(PLAYER_MAXSPEED* PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED* PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED* PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED* PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED* PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED* PLAYER_WALKSPEED),
				}));
			//スキル
			actor->AddAction(Action::Create<EscapeAction>(
				EscapeAction::Parameter{
					AnimParam{
						STATE_KEY_ESCAPE,
						0.2f,
						1.2f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
					Vector3(PLAYER_MAXSPEED * 1.4f, 1.0f, PLAYER_MAXSPEED * 1.4f),
				}));
			//スキル
			actor->AddAction(Action::Create<DropKickSkillAction>(
				DropKickSkillAction::Parameter{
					AnimParam{
						STATE_KEY_DROPKICKSKILL,
						0.0f,
						1.0f,
						0.0f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
					Vector3(PLAYER_MAXSPEED * 2.0f, 1.0f, 1.0f),
					GRAVITY,
					GRAVITYMAX,
					PLAYER_JUMPPOWER * 0.5f,
				}));

			//クリアポーズ
			actor->AddAction(Action::Create<ClearPoseAction>(
				ClearPoseAction::Parameter{
					AnimParam{
						STATE_KEY_CLEARPOSE,
						0.0f,
						1.0f,
						0.0f,
						true
					},
					AnimParam{
						STATE_KEY_JUMP,
						0.83f,
						1.0f,
						0.2f,
						false
					},
					Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
					GRAVITY,
					GRAVITYMAX,
				}));
			return true;
		}
	};
}