#include "ZombieActionCreator.h"
#include "GameDefine.h"

bool ActionGame::ZombieActionCreator::Create(const ActorPtr& actor)
{
	//‘Ò‹@
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
	//ˆÚ“®
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

	//UŒ‚‚P
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
	//UŒ‚‚Q
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

	//ƒ_ƒ[ƒW
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
	//‹ó’†ƒ_ƒ[ƒW
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

	//ƒ_ƒEƒ“
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

	//Ž€–S
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
