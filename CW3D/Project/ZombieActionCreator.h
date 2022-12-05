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
	 * @brief		�A�N�V���������C���^�[�t�F�C�X
	 */
	class ZombieActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ZombieActionCreator() = default;


		/*���p����A�j���[�V�����̖��O
		char* name;
		�A�j���J�n����
		float					startTime;
		�A�j�����x
		float					speed;
		�A�j����Ԏ���
		float					tTime;
		�A�j�����[�v�t���O
		bool					loopFlg;*/

		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor) override {
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
						1.0f,
						0.1f,
						true
					},
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED * 0.5f),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED * 0.5f),
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
			return true;
		}
	};
}