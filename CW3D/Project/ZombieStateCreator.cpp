#include "ZombieStateCreator.h"
#include "GameDefine.h"

using namespace ActionGame;

bool ActionGame::ZombieStateCreator::Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const Input::InputPtr& input)
{
	stateMachine->AddState(CState::Create<CIdleState>(actor, input,
		CIdleState::Parameter{
			5.0f

		}));
	stateMachine->AddState(CState::Create<CMoveState>(actor, input));
	stateMachine->AddState(CState::Create<CDamageState>(actor, input));
	stateMachine->AddState(CState::Create<CFlyDamageState>(actor, input));
	stateMachine->AddState(CState::Create<CDeadState>(actor, input));
	stateMachine->AddState(CState::Create<CDownState>(actor, input,
		CDownState::Parameter{
			2.0f
		}));

	//ダメージエフェクト
	auto damageEffect = std::make_shared<EffectCreateParameter>(
		EffectCreateParameter{ "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f,actor->GetType()});
	stateMachine->AddState(CState::Create<CAttack1State>(actor, input,
		CAttack1State::Parameter{
			2
			,GameFrameTime * 38.0f
			,GameFrameTime * 45.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,CHARA_TYPE::PLAYER, nullptr ,1,0.0f,0,damageEffect,GravityScale(),Vector3(1.2f, 1.0f, 1.0f) }
			,EffectCreateParameter{ "AttackEffect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f,actor->GetType() }

		}));
	stateMachine->AddState(CState::Create<CAttack2State>(actor, input,
		CAttack2State::Parameter{
			2
			,GameFrameTime * 38.0f
			,GameFrameTime * 45.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.0f, 0, Vector3(0.2f, 0.0f, 0.0f),false,CHARA_TYPE::PLAYER, nullptr,2,1.0f,0,damageEffect,GravityScale(), Vector3(1.2f, 1.2f, 1.0f) }

		}));
	stateMachine->AddState(CState::Create<CNPCStartPoseState>(actor, input));

	return true;
}