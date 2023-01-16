#include "MutantStateCreator.h"
#include "GameDefine.h"

bool ActionGame::MutantStateCreator::Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input)
{
	stateMachine->AddState(State::Create<IdleState>(actor, input,
		IdleState::Parameter{
			5.0f

		}));
	stateMachine->AddState(State::Create<MoveState>(actor, input));
	stateMachine->AddState(State::Create<DamageState>(actor, input,
		DamageState::Parameter{
			1.0f
		}));

	stateMachine->AddState(State::Create<DeadState>(actor, input));

	stateMachine->AddState(State::Create<Attack1State>(actor, input,
		Attack1State::Parameter{
			2
			,GameFrameTime * 38.0f
			,GameFrameTime * 45.0f
			,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,CHARA_TYPE::PLAYER, nullptr ,1,0.0f,0,Vector3(3.0f, 1.5f, 2.0f) }
			,EffectCreateParameter{ "AttackEffect3", Vector3(0.8f,0.8f,0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(-90), 0.0f),1.5f }

		}));

	stateMachine->AddState(State::Create<NPCCameraStartPoseState>(actor, input,
		NPCCameraStartPoseState::Parameter{
			3.0f
		}));

    return true;
}
