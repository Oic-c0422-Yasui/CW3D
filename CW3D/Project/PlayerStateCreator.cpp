#include "PlayerStateCreator.h"
#include "GameDefine.h"

bool ActionGame::PlayerStateCreator::Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input)
{
	//�ҋ@
	stateMachine->AddState(State::Create<IdleState>(actor, input,
		IdleState::Parameter{
			5.0f
		}));

	//�ҋ@���[�V����
	stateMachine->AddState(State::Create<IdleMotionState>(actor, input));
	//�ړ�
	stateMachine->AddState(State::Create<MoveState>(actor, input));
	//�W�����v
	stateMachine->AddState(State::Create<JumpState>(actor, input));
	//����
	stateMachine->AddState(State::Create<FallState>(actor, input));
	//���n
	stateMachine->AddState(State::Create<LandingState>(actor, input));
	//�_�b�V��
	stateMachine->AddState(State::Create<RunState>(actor, input));
	//�_�b�V���W�����v
	stateMachine->AddState(State::Create<RunJumpState>(actor, input));
	//�_�b�V������
	stateMachine->AddState(State::Create<RunFallState>(actor, input));
	//�_�b�V�����n
	stateMachine->AddState(State::Create<RunLandingState>(actor, input));
	//�_���[�W
	stateMachine->AddState(State::Create<DamageState>(actor, input,
		DamageState::Parameter{
			1.0f
		}));
	//�󒆃_���[�W
	stateMachine->AddState(State::Create<FlyDamageState>(actor, input));
	//���S
	stateMachine->AddState(State::Create<DeadState>(actor, input));
	//�_�E��
	stateMachine->AddState(State::Create<DownState>(actor, input,
		DownState::Parameter{
			1.0f
		}));

	//�U���P
	stateMachine->AddState(State::Create<Attack1State>(actor, input,
		Attack1State::Parameter{
			2
			,GameFrameTime * 25.0f
			,GameFrameTime * 42.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr ,2,1.0f,0,Vector3(1.2f, 1.5f, 1.0f) }
			,EffectCreateParameter{ "Effect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f }

		}));

	//�U���Q
	stateMachine->AddState(State::Create<Attack2State>(actor, input,
		Attack2State::Parameter{
			2
			,GameFrameTime * 20.0f
			,GameFrameTime * 35.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.0f, 0, Vector3(0.2f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr,2,1.0f,0, Vector3(1.2f, 1.5f, 1.0f) }

		}));

	//�U���R
	stateMachine->AddState(State::Create<Attack3State>(actor, input,
		Attack3State::Parameter{
			2
			,GameFrameTime * 15.0f
			,GameFrameTime * 45.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 0.3f, 0, Vector3(0.3f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,2,1.5f,0, Vector3(1.2f, 2.0f, 1.0f)}

		}));

	//�_�b�V���U���P
	stateMachine->AddState(State::Create<RunAttack1State>(actor, input,
		RunAttack1State::Parameter{
			2
			,GameFrameTime * 20.0f
			,GameFrameTime * 40.0f
			,ShotAABB{ Vector3(0.7f, 0.8f, 0), 0.5f, 0, Vector3(0.4f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr,2,1.5f,0, Vector3(1.2f, 1.5f, 0.8f) }
			,EffectCreateParameter{ "Effect2", Vector3(0.8f, 1.0f, 0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360.0f), 0.0f),2.0f }

		}));

	//�W�����v�U���P
	stateMachine->AddState(State::Create<JumpAttack1State>(actor, input,
		JumpAttack1State::Parameter{
			2
			,GameFrameTime * 20.0f
			,ShotAABB{ Vector3(0.7f, 0.8f, 0), 10.0f, 0, Vector3(0.1f, 0.25f, 0.0f),false,CHARA_PLAYER, nullptr,2,1.0f,0, Vector3(1.0f, 1.2f, 1.0f) }
			,EffectCreateParameter{ "Effect2", Vector3(0.8f,1.0f,0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),2.0f }

		}));

	//�󒆃_�b�V���U���P
	stateMachine->AddState(State::Create<RunJumpAttack1State>(actor, input,
		RunJumpAttack1State::Parameter{
			2
			,GameFrameTime * 15.0f
			,GameFrameTime * 22.0f
			,ShotAABB{ Vector3(0.8f, 0.7f, 0), 10.0f, 0, Vector3(0.35f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,2,1.0f,0, Vector3(1.5f, 1.5f, 1.5f) }
			,EffectCreateParameter{ "Effect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f }

		}));

	//�󒆃_�b�V���U���Q�X�e�[�g
	stateMachine->AddState(State::Create<RunJumpAttack2State>(actor, input,
		RunJumpAttack2State::Parameter{
			2
			,GameFrameTime * 20.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 10.0f, 0, Vector3(0.35f, 0.2f, 0.0f),true,CHARA_PLAYER, nullptr,2,1.0f,0, Vector3(1.5f, 1.5f, 1.5f) }

		}));

	//�󒆃_�b�V���U���R�X�e�[�g
	stateMachine->AddState(State::Create<RunJumpAttack3State>(actor, input,
		RunJumpAttack3State::Parameter{
			2
			,GameFrameTime * 12.0f
			,GameFrameTime * 40.0f
			,ShotAABB{ Vector3(0.7f, 1.2f, 0), 0.3f, 0, Vector3(0.45f, 0.2f, 0.0f),true,CHARA_PLAYER, nullptr,2,1.5f,0, Vector3(1.5f, 2.0f, 1.5f) }

		}));

	//�Ռ��g�X�L���X�e�[�g
	stateMachine->AddState(State::Create<ShockWaveSkillState>(actor, input,
		ShockWaveSkillState::Parameter{
			4
			,GameFrameTime * 40.0f
			,GameFrameTime * 80.0f
			,ShotAABB{ Vector3(5.0f, 0.7f, 0), 0.05f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,4,0.3f,0, Vector3(7.0f, 10.0f, 7.0f) }
			,EffectCreateParameter{ "Effect3", Vector3(0.8f, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.8f }

		}));

	//�r�[���X�L���X�e�[�g
	stateMachine->AddState(State::Create<BeamSkillState>(actor, input,
		BeamSkillState::Parameter{
			3
			,GameFrameTime * 15.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3,0.75f,0, Vector3(5.0f, 2.0f, 2.0f) }
			,ShotOBB{ Vector3(1.0f, 2.0f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3,0.75f,0, Vector3(5.0f, 2.0f, 2.0f), Vector3(0, 0, MOF_ToRadian(30))}
			,EffectCreateParameter{ "Effect4", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f }

		}));

	//�󒆃r�[���X�L���X�e�[�g
	stateMachine->AddState(State::Create<JumpBeamSkillState>(actor, input,
		JumpBeamSkillState::Parameter{
			3
			,GameFrameTime * 15.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3,0.75f,0, Vector3(5.0f, 2.0f, 2.0f) }
			,ShotOBB{ Vector3(2.0f, 1.4f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3,0.75f,0, Vector3(5.0f, 2.0f, 2.0f),Vector3(0, 0, MOF_ToRadian(-30)) }
			,EffectCreateParameter{ "Effect4", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f }

		}));

	//�����X�L���X�e�[�g
	stateMachine->AddState(State::Create<StormSkillState>(actor, input,
		StormSkillState::Parameter{
			3
			,GameFrameTime * 7.0f
			,3.5f
			,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.6f, 0.15f, 0.6f),false,CHARA_PLAYER, nullptr,3,0.5f,0, Vector3(4.0f, 8.0f, 4.0f) }
			,EffectCreateParameter{ "Effect5", Vector3(0, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f }

		}));

	//�󒆗����X�L���X�e�[�g
	stateMachine->AddState(State::Create<JumpStormSkillState>(actor, input,
		JumpStormSkillState::Parameter{
			3
			,GameFrameTime * 7.0f
			,3.5f
			,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.6f, 0.15f, 0.6f),false,CHARA_PLAYER,nullptr,3,0.5f,0, Vector3(4.0f, 8.0f, 4.0f) }
			,EffectCreateParameter{ "Effect5", Vector3(0, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f }

		}));

	//����X�e�[�g
	stateMachine->AddState(State::Create<EscapeState>(actor, input,
		EscapeState::Parameter{
			2
			,GameFrameTime * 5.0f
			,GameFrameTime * 35.0f
			,GameFrameTime * 0.0f
			,GameFrameTime * 10.0f
		}));

	//�N���A�|�[�Y�X�e�[�g
	stateMachine->AddState(State::Create<ClearPoseState>(actor, input));

	//�J�n�|�[�Y�X�e�[�g
	stateMachine->AddState(State::Create<StartPoseState>(actor, input,
		StartPoseState::Parameter{
			5.0
		}));
	
	//�h���b�v�L�b�N�X�L���X�e�[�g
	stateMachine->AddState(State::Create<DropKickSkillState>(actor, input,
		DropKickSkillState::Parameter{
			3
			,GameFrameTime * 5.0f
			,GameFrameTime * 30.0f
			,ShotAABB{ Vector3(1.0f, 0.7f, 0), 2.0f, 0, Vector3(0.7f, 0.32f, 0.0f),false,CHARA_PLAYER, nullptr,4,3.5f,0, Vector3(4.0f, 3.0f, 3.0f) }
			,EffectCreateParameter{ "Effect7", Vector3(5.5f, 1.2f, 0), Vector3(0.3f, 0.3f, 0.3f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.8f }

		}));

	return true;
}
