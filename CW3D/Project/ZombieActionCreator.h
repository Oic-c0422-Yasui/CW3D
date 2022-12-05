#pragma once

#include	"IActionCreator.h"
#include	"IdleAction.h"
#include	"MoveAction.h"

#include	"Attack1Action.h"
#include	"Attack2Action.h"

#include	"FlyDamageAction.h"
#include	"DownAction.h"

#include	"DamageAction.h"
#include	"DeadAction.h"


namespace ActionGame {
	/**
	 * @brief		アクション生成インターフェイス
	 */
	class ZombieActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ZombieActionCreator() = default;


		/*利用するアニメーションの名前
		char* name;
		アニメ開始時間
		float					startTime;
		アニメ速度
		float					speed;
		アニメ補間時間
		float					tTime;
		アニメループフラグ
		bool					loopFlg;*/

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
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f),
					GRAVITYMAX,
				}));

			//攻撃１
			actor->AddAction(Action::Create<Attack1Action>(
				Attack1Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK1,
						0.0f,
						1.2f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
				}));
			//攻撃２
			actor->AddAction(Action::Create<Attack2Action>(
				Attack2Action::Parameter{
					AnimParam{
						STATE_KEY_ATTACK1,
						0.0f,
						1.3f,
						0.1f,
						false
					},
					Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
					Vector3(0.1f, 0.0f, 0.0f),
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
					1.5f,
				}));
			return true;
		}
	};
}