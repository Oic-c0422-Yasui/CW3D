#include "PlayerStateCreator.h"
#include "GameDefine.h"

bool ActionGame::PlayerStateCreator::Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const Input::InputPtr& input)
{
	//�ҋ@
	stateMachine->AddState(CState::Create<CIdleState>(actor, input,
		CIdleState::Parameter{
			5.0f
		}));

	//�ҋ@���[�V����
	stateMachine->AddState(CState::Create<CIdleMotionState>(actor, input));
	//�ړ�
	stateMachine->AddState(CState::Create<CMoveState>(actor, input));
	//�W�����v
	stateMachine->AddState(CState::Create<CJumpState>(actor, input));
	//����
	stateMachine->AddState(CState::Create<CFallState>(actor, input));
	//���n
	stateMachine->AddState(CState::Create<CLandingState>(actor, input));
	//�_�b�V��
	stateMachine->AddState(CState::Create<CRunState>(actor, input));
	//�_�b�V���W�����v
	stateMachine->AddState(CState::Create<CRunJumpState>(actor, input));
	//�_�b�V������
	stateMachine->AddState(CState::Create<CRunFallState>(actor, input));
	//�_�b�V�����n
	stateMachine->AddState(CState::Create<CRunLandingState>(actor, input));
	//�_���[�W
	stateMachine->AddState(CState::Create<CDamageState>(actor, input));
	//�󒆃_���[�W
	stateMachine->AddState(CState::Create<CFlyDamageState>(actor, input));
	//���S
	stateMachine->AddState(CState::Create<CDeadState>(actor, input));
	//�_�E��
	stateMachine->AddState(CState::Create<CDownState>(actor, input,
		CDownState::Parameter{
			1.0f
		}));

	//�_���[�W�G�t�F�N�g
	auto damageEffect = std::make_shared<EffectCreateParameter>(
		EffectCreateParameter{ "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f,actor->GetType()});
	//�U���P
	stateMachine->AddState(CState::Create<CAttack1State>(actor, input,
		CAttack1State::Parameter{
			2
			,GameFrameTime * 20.0f
			,GameFrameTime * 32.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,actor->GetType(), nullptr ,2,2.5f,0,damageEffect,GravityScaleParam(),Vector3(1.2f, 1.5f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }
			

		}));

	//�U���Q
	stateMachine->AddState(CState::Create<CAttack2State>(actor, input,
		CAttack2State::Parameter{
			2
			,GameFrameTime * 10.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.0f, 0, Vector3(0.2f, 0.0f, 0.0f),false,actor->GetType(), nullptr,2,2.5f,0,damageEffect,GravityScaleParam(), Vector3(1.2f, 1.5f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }

		}));

	//�U���R
	auto gravity = GravityScaleParam{true,2.0f,0.01f,1.0f};
	stateMachine->AddState(CState::Create<CAttack3State>(actor, input,
		CAttack3State::Parameter{
			2
			,GameFrameTime * 10.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 0.15f, 15, Vector3(0.3f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,3.5f,0,damageEffect,gravity, Vector3(1.5f, 2.5f, 1.5f)}

		}));

	//�_�b�V���U���P
	stateMachine->AddState(CState::Create<CRunAttack1State>(actor, input,
		CRunAttack1State::Parameter{
			2
			,GameFrameTime * 10.0f
			,GameFrameTime * 30.0f
			,ShotAABB{ Vector3(0.7f, 0.8f, 0), 0.5f, 0, Vector3(0.6f, 0.0f, 0.0f),false,actor->GetType(), nullptr,2,3.0f,0,damageEffect,GravityScaleParam(), Vector3(1.7f, 1.5f, 0.8f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f, 1.0f, 0), Vector3(0.6f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360.0f), 0.0f),2.1f,actor->GetType() }

		}));

	//�_�b�V���U���Q
	stateMachine->AddState(CState::Create<CRunAttack2State>(actor, input,
		CRunAttack2State::Parameter{
			2
			,GameFrameTime * 20.0f
			,GameFrameTime * 32.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,actor->GetType(), nullptr ,2,2.5f,0,damageEffect,GravityScaleParam(),Vector3(1.2f, 1.5f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }

		}));

	//�W�����v�U���P
	stateMachine->AddState(CState::Create<CJumpAttack1State>(actor, input,
		CJumpAttack1State::Parameter{
			2
			,GameFrameTime * 20.0f
			,ShotAABB{ Vector3(0.7f, 0.8f, 0), 10.0f, 0, Vector3(0.1f, 0.25f, 0.0f),false,actor->GetType(), nullptr,2,2.0f,0,damageEffect,gravity, Vector3(1.0f, 1.2f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,1.0f,0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),2.0f,actor->GetType() }

		}));

	//�󒆃_�b�V���U���P
	stateMachine->AddState(CState::Create<CRunJumpAttack1State>(actor, input,
		CRunJumpAttack1State::Parameter{
			2
			,GameFrameTime * 15.0f
			,GameFrameTime * 22.0f
			,ShotAABB{ Vector3(0.8f, 0.7f, 0), 10.0f, 0, Vector3(0.35f, 0.2f, 0.0f),false,actor->GetType(), nullptr,2,2.0f,0,damageEffect,gravity, Vector3(1.5f, 1.5f, 1.5f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }

		}));

	//�󒆃_�b�V���U���Q�X�e�[�g
	stateMachine->AddState(CState::Create<CRunJumpAttack2State>(actor, input,
		CRunJumpAttack2State::Parameter{
			2
			,GameFrameTime * 20.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 10.0f, 0, Vector3(0.35f, 0.2f, 0.0f),true,actor->GetType(), nullptr,2,2.0f,0,damageEffect,gravity, Vector3(1.5f, 1.5f, 1.5f) }

		}));

	//�󒆃_�b�V���U���R�X�e�[�g
	stateMachine->AddState(CState::Create<CRunJumpAttack3State>(actor, input,
		CRunJumpAttack3State::Parameter{
			2
			,GameFrameTime * 12.0f
			,GameFrameTime * 40.0f
			,ShotAABB{ Vector3(0.7f, 1.2f, 0), 0.3f, 0, Vector3(0.45f, 0.2f, 0.0f),true,actor->GetType(), nullptr,2,3.5f,0,damageEffect,gravity, Vector3(1.5f, 2.0f, 1.5f) }

		}));

	//�Ռ��g�X�L���X�e�[�g
	stateMachine->AddState(CState::Create<CShockWaveSkillState>(actor, input,
		CShockWaveSkillState::Parameter{
			4
			,GameFrameTime * 40.0f
			,GameFrameTime * 80.0f
			,ShotAABB{ Vector3(5.0f, 0.7f, 0), 0.05f, 0, Vector3(-0.3f, 0.15f, -0.3f),false,actor->GetType(), nullptr,4,0.0f,0,nullptr,GravityScaleParam(), Vector3(7.0f, 10.0f, 7.0f) }
			,EffectCreateParameter{ "SkillEffect1", Vector3(0.8f, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.8f,actor->GetType() }

		}));

	//�r�[���X�L���X�e�[�g
	stateMachine->AddState(CState::Create<CBeamSkillState>(actor, input,
		CBeamSkillState::Parameter{
			3
			,GameFrameTime * 15.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,3,0.2f,0,damageEffect,GravityScaleParam(), Vector3(5.0f, 2.0f, 2.0f) }
			,ShotOBB{ Vector3(1.0f, 2.0f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,3,0.2f,0,damageEffect,GravityScaleParam(), Vector3(5.0f, 2.0f, 2.0f), Vector3(0, 0, MOF_ToRadian(30))}
			,EffectCreateParameter{ "SkillEffect2", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f,actor->GetType() }

		}));

	//�󒆃r�[���X�L���X�e�[�g
	stateMachine->AddState(CState::Create<CJumpBeamSkillState>(actor, input,
		CJumpBeamSkillState::Parameter{
			3
			,GameFrameTime * 15.0f
			,GameFrameTime * 25.0f
			,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,3,0.2f,0,damageEffect,GravityScaleParam(), Vector3(5.0f, 2.0f, 2.0f) }
			,ShotOBB{ Vector3(2.0f, 1.4f, 0), 0.0f, 0, Vector3(0.05f, 0.2f, 0.0f),false,actor->GetType(), nullptr,3,0.2f,0,damageEffect,GravityScaleParam(), Vector3(5.0f, 2.0f, 2.0f),Vector3(0, 0, MOF_ToRadian(-30)) }
			,EffectCreateParameter{ "SkillEffect2", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f,actor->GetType() }

		}));

	//�����X�L���X�e�[�g
	gravity = GravityScaleParam{ true,1.0f,0.01f,1.0f };
	stateMachine->AddState(CState::Create<CStormSkillState>(actor, input,
		CStormSkillState::Parameter{
			3
			,GameFrameTime * 7.0f
			,3.5f
			,1.0f
			,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.6f, 0.1f, 0.6f),false,actor->GetType(), nullptr,3,0.2f,0,damageEffect,gravity, Vector3(4.0f, 8.0f, 4.0f) }
			,EffectCreateParameter{ "SkillEffect3", Vector3(0, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f,actor->GetType() }

		}));

	//�󒆗����X�L���X�e�[�g
	stateMachine->AddState(CState::Create<CJumpStormSkillState>(actor, input,
		CJumpStormSkillState::Parameter{
			3
			,GameFrameTime * 7.0f
			,3.5f
			,1.0f
			,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.6f, 0.1f, 0.6f),false,actor->GetType(),nullptr,3,0.2f,0,damageEffect,gravity, Vector3(4.0f, 8.0f, 4.0f) }
			,EffectCreateParameter{ "SkillEffect3", Vector3(0, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f,actor->GetType() }

		}));

	//����X�e�[�g
	stateMachine->AddState(CState::Create<CEscapeState>(actor, input,
		CEscapeState::Parameter{
			2
			,GameFrameTime * 5.0f
			,GameFrameTime * 25.0f
			,GameFrameTime * 10.0f
			,GameFrameTime * 0.0f
			,GameFrameTime * 7.0f
		}));

	//�N���A�|�[�Y�X�e�[�g
	stateMachine->AddState(CState::Create<CClearPoseState>(actor, input));

	//�J�n�|�[�Y�X�e�[�g
	stateMachine->AddState(CState::Create<CStartPoseState>(actor, input,
		CStartPoseState::Parameter{
			3.0
		}));
	
	//�h���b�v�L�b�N�X�L���X�e�[�g
	stateMachine->AddState(CState::Create<CDropKickSkillState>(actor, input,
		CDropKickSkillState::Parameter{
			3
			,GameFrameTime * 5.0f
			,GameFrameTime * 30.0f
			,ShotAABB{ Vector3(1.0f, 0.7f, 0), 2.0f, 0, Vector3(0.7f, 0.32f, 0.0f),false,actor->GetType(), nullptr,4,1.0f,0,damageEffect,GravityScaleParam(), Vector3(4.0f, 3.0f, 3.0f) }
			,EffectCreateParameter{ "SkillEffect5", Vector3(5.5f, 1.2f, 0), Vector3(0.3f, 0.3f, 0.3f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.8f,actor->GetType() }

		}));

	//���W�����v�X�L���X�e�[�g
	stateMachine->AddState(CState::Create<CFlyHighSkillState>(actor, input,
		CFlyHighSkillState::Parameter{
			2
			,GameFrameTime * 5.0f
			,GameFrameTime * 30.0f
			,GameFrameTime * 0.0f
			,GameFrameTime * 7.0f
			,ShotAABB{ Vector3(0.0f, -1.0f, 0), 2.5f, 0, Vector3(0.0f, 0.35f, 0.0f),false,actor->GetType(), nullptr,3,1.0f,0,damageEffect,gravity, Vector3(2.0f, 3.0f, 2.0f) }
			,EffectCreateParameter{ "SkillEffect4", Vector3(0, 1.2f, 0), Vector3(0.5f, 1.0f, 0.5f), Vector3(MOF_ToRadian(180), 0.0f, 0.0f),1.8f,actor->GetType() }
		}));


	return true;
}
