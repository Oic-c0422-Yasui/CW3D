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
	 * @brief		�A�N�V���������C���^�[�t�F�C�X
	 */
	class PlayerActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~PlayerActionCreator() = default;


		/*
		���p����A�j���[�V�����̖��O
		char*					name;
		�A�j���J�n����
		float					startTime;
		�A�j�����x
		float					speed;
		�A�j����Ԏ���
		float					tTime;
		�A�j�����[�v�t���O
		bool					loopFlg;
		*/

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
			//�ҋ@���[�V����
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
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
					Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
					GRAVITYMAX,
				}));
			//�_�b�V��
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
			//�W�����v
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
			//�_�b�V���W�����v
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
			//����
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
			//�_�b�V������
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
			//���n
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
			//�W�����v���n
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

			//�U���P
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

			//�U���Q
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

			//�U���R
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

			//�_�b�V���U���P
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

			//�W�����v�U���P
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

			//�_�b�V���W�����v�U���P
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
			//�_�b�V���W�����v�U���Q
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
			//�_�b�V���W�����v�U���R
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
					2.0f,
				}));

			//�X�L��
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

			//�X�L��
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
			//�X�L��
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
			//�󒆃X�L��
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
			//�󒆃X�L��
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
			//�X�L��
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
			//�X�L��
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

			//�N���A�|�[�Y
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