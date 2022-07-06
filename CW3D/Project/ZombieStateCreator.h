#pragma once

#include	"IStateCreator.h"
#include "IdleState.h"
#include "MoveState.h"
#include "Attack1State.h"

#include "DamageState.h"
#include "FlyDamageState.h"
#include "DownState.h"
#include "DeadState.h"




namespace Sample {

	/**
	 * @brief		ステート生成インターフェイス
	 */
	class ZombieStateCreator : public IStateCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ZombieStateCreator() = default;

		/**
		 * @brief		生成
		 */
		bool Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input) override {
			stateMachine->AddState(State::Create<IdleState>(actor, input,
				IdleState::Parameter{
					5.0f

				}));
			stateMachine->AddState(State::Create<MoveState>(actor, input));
			stateMachine->AddState(State::Create<DamageState>(actor, input,
				DamageState::Parameter{
					1.0f
				}));
			stateMachine->AddState(State::Create<FlyDamageState>(actor, input));
			stateMachine->AddState(State::Create<DeadState>(actor, input));
			stateMachine->AddState(State::Create<DownState>(actor, input,
				DownState::Parameter{
					3.0f
				}));

			stateMachine->AddState(State::Create<Attack1State>(actor, input,
				Attack1State::Parameter{
					2
					,GameFrameTime * 40.0f
					,GameFrameTime * 42.0f
					,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr ,1,0.0f,0,Vector3(0.8f, 1.0f, 1.0f) }
					,EffectCreateParameter{ "Effect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f }

				}));

			return true;
		}
	};
}