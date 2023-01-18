#include "PlayerActionCreator.h"
#include "GameDefine.h"



bool ActionGame::PlayerActionCreator::Create(const ActorPtr& actor)
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
	//�ҋ@���[�V����
	actor->AddAction(Action::Create<IdleMotionAction>(
		IdleMotionAction::Parameter{
			AnimParam{
				STATE_KEY_IDLE_MOTION,
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
				STATE_KEY_RUN_ATTACK1,
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
				STATE_KEY_RUN_ATTACK1,
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
			2.0f,
		}));

	//�Ռ��g�X�L��
	actor->AddAction(Action::Create<ShockWaveSkillAction>(
		ShockWaveSkillAction::Parameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				0.7f,
				0.1f,
				false
			},
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));

	//�r�[���X�L��
	actor->AddAction(Action::Create<BeamSkillAction>(
		BeamSkillAction::Parameter{
			AnimParam{
				STATE_KEY_BEAM_SKILL,
				0.7f,
				2.0f,
				0.1f,
				false
			},
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//�����X�L��
	actor->AddAction(Action::Create<StormSkillAction>(
		StormSkillAction::Parameter{
			AnimParam{
				STATE_KEY_STORM_SKILL,
				0.0f,
				0.6f,
				0.1f,
				true
			},
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
		}));
	//�󒆃r�[���X�L��
	actor->AddAction(Action::Create<JumpBeamSkillAction>(
		JumpBeamSkillAction::Parameter{
			AnimParam{
				STATE_KEY_BEAM_SKILL,
				0.7f,
				2.0f,
				0.1f,
				false
			},
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//�󒆗����X�L��
	actor->AddAction(Action::Create<JumpStormSkillAction>(
		JumpStormSkillAction::Parameter{
			AnimParam{
				STATE_KEY_STORM_SKILL,
				0.0f,
				0.6f,
				0.1f,
				true
			},
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
		}));
	//���
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
	//�h���b�v�L�b�N�X�L��
	actor->AddAction(Action::Create<DropKickSkillAction>(
		DropKickSkillAction::Parameter{
			AnimParam{
				STATE_KEY_DROPKICK_SKILL,
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

	//�J�n�|�[�Y
	actor->AddAction(Action::Create<StartPoseAction>(
		StartPoseAction::Parameter{
			AnimParam{
				STATE_KEY_STARTPOSE,
				0.0f,
				1.0f,
				0.0f,
				false
			},
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));

	return true;
}
