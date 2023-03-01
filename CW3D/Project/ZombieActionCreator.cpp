#include "ZombieActionCreator.h"
#include "GameDefine.h"

bool ActionGame::ZombieActionCreator::Create(const ActorPtr& actor)
{
	//待機
	actor->AddAction(CAction::Create<CIdleAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_IDLE,
				0.0f,
				1.0f,
				0.25f,
				true
			}
		},
		CIdleAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f,PLAYER_SPEED * 0.3f),
			Vector3(PLAYER_SPEED, 1.0f,PLAYER_SPEED)
		}));
	//移動
	actor->AddAction(CAction::Create<CMoveAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_MOVE,
				0.0f,
				1.5f,
				0.1f,
				true
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f),
			GRAVITYMAX,
		}));

	//攻撃１
	actor->AddAction(CAction::Create<CAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CAttack1Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//攻撃２
	actor->AddAction(CAction::Create<CAttack2Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.3f,
				0.1f,
				false
			}
		},
		CAttack2Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(0.1f, 0.0f, 0.0f),
		}));

	//ダメージ
	actor->AddAction(CAction::Create<CDamageAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DAMAGE,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CDamageAction::Parameter{
			
			Vector3(0.05f, 1.0f, 0.05f),
			GRAVITY,
			GRAVITYMAX,
		}));
	//空中ダメージ
	actor->AddAction(CAction::Create<CFlyDamageAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_FLY_DAMAGE,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CFlyDamageAction::Parameter{
			Vector3(0.05f, 1.0f, 0.05f),
			GRAVITY,
			GRAVITYMAX * 0.4f,
		}));

	//ダウン
	actor->AddAction(CAction::Create<CDownAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DOWN,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CDownAction::Parameter{
			Vector3(0.05f, 1.0f, 0.05f),
		}));

	//死亡
	actor->AddAction(CAction::Create<CDeadAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DOWN,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CDeadAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			1.5f,
		}));

	//開始ポーズ
	actor->AddAction(CAction::Create<CNPCStartPoseAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STARTPOSE,
				0.0f,
				1.5f,
				0.2f,
				false
			}
		},
		CNPCStartPoseAction::Parameter{
			Vector3(0.0f, 0.0f, 0.0f),
			2.0f,
		}));

	return true;
}
