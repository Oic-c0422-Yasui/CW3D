#include "ZombieActionCreator.h"
#include "GameDefine.h"

bool ActionGame::ZombieActionCreator::Create(const ActorPtr& actor)
{
	//�ҋ@
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
	//�ړ�
	actor->AddAction(Action::Create<MoveAction>(
		MoveAction::Parameter{
			AnimParam{
				STATE_KEY_MOVE,
				0.0f,
				1.5f,
				0.1f,
				true
			},
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.3f),
			GRAVITYMAX,
		}));

	//�U���P
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
	//�U���Q
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

	//�_���[�W
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
	//�󒆃_���[�W
	actor->AddAction(Action::Create<CFlyDamageAction>(
		CFlyDamageAction::Parameter{
			AnimParam{
				STATE_KEY_FLY_DAMAGE,
				0.0f,
				1.2f,
				0.1f,
				false
			},
			Vector3(0.05f, 1.0f, 0.05f),
			GRAVITY,
			GRAVITYMAX * 0.4f,
		}));

	//�_�E��
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

	//���S
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

	//�J�n�|�[�Y
	actor->AddAction(Action::Create<NPCStartPoseAction>(
		NPCStartPoseAction::Parameter{
			AnimParam{
				STATE_KEY_STARTPOSE,
				0.0f,
				1.5f,
				0.2f,
				false
			},
			Vector3(0.0f, 0.0f, 0.0f),
			2.0f,
		}));

	return true;
}
