#include "PlayerActionCreator.h"
#include "GameDefine.h"


bool ActionGame::PlayerActionCreator::Create(const ActorPtr& actor)
{


	//�ҋ@
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
	//�ҋ@���[�V����
	actor->AddAction(CAction::Create<IdleMotionAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_IDLE_MOTION,
				0.0f,
				1.0f,
				0.3f,
				false
			}
		},
		IdleMotionAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED)
		}));
	//�ړ�
	actor->AddAction(CAction::Create<CMoveAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_MOVE,
				0.0f,
				1.0f,
				0.1f,
				true
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			GRAVITYMAX,
		}));
	//�_�b�V��
	actor->AddAction(STATE_KEY_RUN, CAction::Create<CMoveAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_RUN,
				0.0f,
				1.0f,
				0.12f,
				true
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITYMAX,
		}));
	//�W�����v
	actor->AddAction(CAction::Create<CJumpAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.3f,
				2.0f,
				0.1f,
				false
			}
		},
		CJumpAction::Parameter{
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			GRAVITY,
			GRAVITYMAX,
			PLAYER_JUMPPOWER,
		}));
	//�_�b�V���W�����v
	actor->AddAction(CAction::Create<CRunJumpAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.3f,
				2.0f,
				0.1f,
				false
			}
		},
		CMoveAction::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_SPEED, PLAYER_JUMPPOWER, PLAYER_SPEED),
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));
	//����
	actor->AddAction(CAction::Create<CFallAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.81f,
				2.0f,
				0.1f,
				false
			}
		},
		CFallAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));
	//�_�b�V������
	actor->AddAction(CAction::Create<CRunFallAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_JUMP,
				0.81f,
				2.0f,
				0.1f,
				false
			}
		},
		CRunFallAction::Parameter{
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));
	//���n
	actor->AddAction(CAction::Create<CLandingAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_LANDING,
				0.0f,
				1.0f,
				0.1f,
				false
			}
		},
		CLandingAction::Parameter{
			
		}));
	//�W�����v���n
	actor->AddAction(CAction::Create<CRunLandingAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_LANDING,
				0.0f,
				1.0f,
				0.1f,
				false
			}
		},
		CRunLandingAction::Parameter{
			
		}));

	//�U���P
	actor->AddAction(CAction::Create<CAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CAttack1Action::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(0.2f, 1.0f, 1.0f),
		}));

	//�U���Q
	actor->AddAction(CAction::Create<CAttack2Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK2,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CAttack2Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(0.1f, 0.0f, 0.0f),
		}));

	//�U���R
	actor->AddAction(CAction::Create<CAttack3Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK3,
				0.0f,
				1.7f,
				0.1f,
				false
			}
		},
		CAttack3Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(0.05f, 0.0f, 0.0f),
			Vector3(0.1f, 0.0f, 0.0f),
		}));

	//�_�b�V���U���P
	actor->AddAction(CAction::Create<CRunAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_RUN_ATTACK1,
				0.3f,
				1.0f,
				0.1f,
				false
			}
		},
		CRunAttack1Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//�_�b�V���U���Q
	actor->AddAction(STATE_KEY_RUN_ATTACK2,CAction::Create<CAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CAttack1Action::Parameter{
			Vector3(PLAYER_SPEED, 1.0f, PLAYER_SPEED),
			Vector3(0.2f, 1.0f, 1.0f),
		}));

	//�W�����v�U���P
	actor->AddAction(CAction::Create<CJumpAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_RUN_ATTACK1,
				0.0f,
				1.2f,
				0.1f,
				false
			}
		},
		CJumpAttack1Action::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			GRAVITY,
		}));

	//�_�b�V���W�����v�U���P
	actor->AddAction(CAction::Create<CRunJumpAttack1Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				1.7f,
				0.1f,
				false
			}
		},
		CRunJumpAttack1Action::Parameter{
			Vector3(0.25f, 0.0f, 0.0f),
			PLAYER_JUMPPOWER * 0.4f,
			GRAVITY * 0.7f,
			GRAVITY,
		}));
	//�_�b�V���W�����v�U���Q
	actor->AddAction(CAction::Create<CRunJumpAttack2Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK2,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CRunJumpAttack2Action::Parameter{
			Vector3(0.25f, 0.0f,0.0f),
			PLAYER_JUMPPOWER * 0.4f,
			GRAVITY * 0.7f,
			GRAVITY,
		}));
	//�_�b�V���W�����v�U���R
	actor->AddAction(CAction::Create<CRunJumpAttack3Action>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK3,
				0.0f,
				1.5f,
				0.1f,
				false
			}
		},
		CRunJumpAttack3Action::Parameter{
			Vector3(0.25f, 0.0f, 0.0f),
			PLAYER_JUMPPOWER * 0.4f,
			GRAVITY * 0.7f,
			GRAVITY,
		}));

	//�_���[�W
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
	//�󒆃_���[�W
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

	//�_�E��
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

	//���S
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
			2.0f,
		}));

	//�Ռ��g�X�L��
	actor->AddAction(CAction::Create<CShockWaveSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ATTACK1,
				0.0f,
				0.7f,
				0.1f,
				false
			}
		},
		CShockWaveSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));

	//�r�[���X�L��
	actor->AddAction(CAction::Create<CBeamSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_BEAM_SKILL,
				1.0f,
				2.2f,
				0.1f,
				false
			}
		},
		CBeamSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//�����X�L��
	actor->AddAction(CAction::Create<CStormSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STORM_SKILL,
				0.0f,
				1.2f,
				0.1f,
				true
			}
		},
		CStormSkillAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
		}));
	//�󒆃r�[���X�L��
	actor->AddAction(CAction::Create<CJumpBeamSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_BEAM_SKILL,
				1.0f,
				2.2f,
				0.1f,
				false
			}
		},
		CJumpBeamSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
		}));
	//�󒆗����X�L��
	actor->AddAction(CAction::Create<CJumpStormSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STORM_SKILL,
				0.0f,
				1.2f,
				0.1f,
				true
			}
		},
		CJumpStormSkillAction::Parameter{
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_SPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_SPEED * PLAYER_WALKSPEED),
			Vector3(PLAYER_MAXSPEED * PLAYER_WALKSPEED, 1.0f, PLAYER_MAXSPEED * PLAYER_WALKSPEED),
		}));
	//���
	actor->AddAction(CAction::Create<CEscapeAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_ESCAPE,
				0.4f,
				2.0f,
				0.1f,
				false
			}
		},
		CEscapeAction::Parameter{
			Vector3(PLAYER_SPEED * 0.5f, 1.0f, PLAYER_SPEED * 0.5f),
			Vector3(PLAYER_MAXSPEED * 1.7f, 1.0f, PLAYER_MAXSPEED * 1.7f),
		}));
	//�h���b�v�L�b�N�X�L��
	actor->AddAction(CAction::Create<CDropKickSkillAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_DROPKICK_SKILL,
				0.0f,
				1.0f,
				0.0f,
				false
			}
		},
		CDropKickSkillAction::Parameter{
			Vector3(PLAYER_SPEED * 0.3f, 1.0f, PLAYER_SPEED * 0.3f),
			Vector3(PLAYER_MAXSPEED * 2.0f, 1.0f, 1.0f),
			GRAVITY,
			GRAVITYMAX,
			PLAYER_JUMPPOWER * 0.5f,
		}));

	//�N���A�|�[�Y
	actor->AddAction(CAction::Create<ClearPoseAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_CLEARPOSE,
				0.0f,
				1.0f,
				0.0f,
				true
			}
		},
		ClearPoseAction::Parameter{
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
	actor->AddAction(CAction::Create<CStartPoseAction>(
		CBaseAction::BaseParameter{
			AnimParam{
				STATE_KEY_STARTPOSE,
				0.0f,
				1.0f,
				0.0f,
				false
			}
		},
		CStartPoseAction::Parameter{
			Vector3(PLAYER_MAXSPEED, 1.0f, PLAYER_MAXSPEED),
			GRAVITY,
			GRAVITYMAX,
		}));

	/*
	* �ړ��␳
	*/

	const auto type = actor->GetType();

	//�U���P
	const std::string str = STATE_KEY_MOVECOMPENSATION;
	actor->AddAction(str + STATE_KEY_ATTACK1,CAction::Create<CMoveCompensationAction>(
		CMoveCompensationAction::BaseParameter{ true, false, 0.5f, 270.0f, 4.5f, type }
		));
	//�U���Q
	actor->AddAction(str + STATE_KEY_ATTACK2, CAction::Create<CMoveCompensationAction>(
		CMoveCompensationAction::BaseParameter{ true, false, 0.5f, 90.0f, 2.5f, type }
		));
	//�_�b�V���U���P
	actor->AddAction(str + STATE_KEY_RUN_ATTACK1, CAction::Create<CMoveCompensationAction>(
		CMoveCompensationAction::BaseParameter{ true, false, 0.5f, 270.0f, 4.5f, type }
		));
	//�_�b�V���U���Q
	actor->AddAction(str + STATE_KEY_RUN_ATTACK2, CAction::Create<CMoveCompensationAction>(
		CMoveCompensationAction::BaseParameter{ true, false, 0.5f, 90.0f, 4.5f, type }
		));


	return true;
}
