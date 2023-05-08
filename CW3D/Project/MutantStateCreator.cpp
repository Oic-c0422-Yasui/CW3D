#include "MutantStateCreator.h"
#include "GameDefine.h"
#include "IdleState.h"
#include "MoveState.h"
#include "Attack1State.h"
#include "DeadState.h"
#include "DamageState.h"
#include "NPCCameraStartPoseState.h"
#include "SpearAttackState.h"
#include "TackleAttackState.h"
#include "TiredState.h"
#include "SlashAttackState.h"

bool ActionGame::MutantStateCreator::Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const Input::InputPtr& input)
{
	stateMachine->AddState(CState::Create<CIdleState>(actor, input,
		CIdleState::Parameter{
			5.0f
		}));
	stateMachine->AddState(CState::Create<CTiredState>(actor, input,
		CTiredState::Parameter{
			3.0f
		}));
	stateMachine->AddState(CState::Create<CMoveState>(actor, input));
	stateMachine->AddState(CState::Create<CDamageState>(actor, input,
		CDamageState::Parameter{
			3
		}));
	stateMachine->AddState(CState::Create<CDeadState>(actor, input));

	//ダメージエフェクト
	auto damageEffect = std::make_shared<EffectCreateParameter>(
		EffectCreateParameter{ "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f,actor->GetType() });
	
	stateMachine->AddState(CState::Create<CAttack1State>(actor, input,
		CAttack1State::Parameter{
			2
			,GameFrameTime * 50.0f
			,GameFrameTime * 60.0f
			,GameFrameTime * 55.0f
			,ShotAABB{ Vector3(2.5f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,CHARA_TYPE::PLAYER, nullptr ,1,0.0f,0,damageEffect,GravityScale(),Vector3(3.0f, 1.5f, 2.0f)}
			,EffectCreateParameter{ "AttackEffect3", Vector3(0.8f,0.8f,0), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.5f,actor->GetType() }
		}));

	stateMachine->AddState(CState::Create<CNPCFollowCameraStartPoseState>(actor, input,
		CNPCFollowCameraStartPoseState::Parameter{
			3.0f
			,EffectCreateParameter{ "RoarEffect", Vector3(0.0f,1.0f,0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f,actor->GetType() }
			,1.0f
		}));
	stateMachine->AddState(CState::Create<CSpearAttackState>(actor, input,
		CSpearAttackState::Parameter{
			5
			,GameFrameTime * 108.0f
			,GameFrameTime * 135.0f
			,GameFrameTime * 200.0f
			,ShotAABB{ Vector3(0.0f, 0.7f, 0), 2.5f, 100, Vector3(0.3f, 0.3f, 0.3f),false,CHARA_TYPE::PLAYER, nullptr ,4,0.0f,0,damageEffect,GravityScale(),Vector3(6.0f, 3.5f, 5.0f)}
			,EffectCreateParameter{ "BossAttackEffect", Vector3(0.0f,0.1f,0.0f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.0f,actor->GetType() }

		}));
	stateMachine->AddState(CState::Create<CTackleAttackState>(actor, input,
		CTackleAttackState::Parameter{
			3
			,GameFrameTime * 50.0f
			,ShotAABB{ Vector3(0.0f, 0.7f, 0), 2.5f, 5, Vector3(0.3f, 0.3f, 0.3f),false,CHARA_TYPE::PLAYER, nullptr ,4,0.0f,0,damageEffect,GravityScale(),Vector3(2.0f, 2.0f, 2.0f)}
			,EffectCreateParameter{ "AttackEffect3", Vector3(0.0f,0.1f,0.0f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.0f,actor->GetType() }

		}));
	stateMachine->AddState(CState::Create<CSlashAttackState>(actor, input,
		CSlashAttackState::Parameter{
			3
			,GameFrameTime * 38.0f
			,GameFrameTime * 60.0f
			,GameFrameTime * 80.0f
			,GameFrameTime * 150.0f
			,ShotAABB{ Vector3(2.5f, 0.7f, 0), 2.5f, 0, Vector3(0.8f, 0.2f, -0.8f),false,CHARA_TYPE::PLAYER, nullptr ,4,0.0f,0,damageEffect,GravityScale(),Vector3(2.5f, 2.0f, 1.5f)}
			,EffectCreateParameter{ "AttackEffect3", Vector3(0.0f,0.1f,0.0f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.0f,actor->GetType() }

		}));


    return true;
}
