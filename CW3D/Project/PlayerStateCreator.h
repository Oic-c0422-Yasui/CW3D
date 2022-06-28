#pragma once

#include	"IStateCreator.h"
#include "IdleState.h"
#include "MoveState.h"
#include "RunState.h"
#include "IdleMotionState.h"
#include "Attack1State.h"
#include "Attack2State.h"
#include "Attack3State.h"
#include "RunAttack1State.h"
#include "Skill1_1State.h"
#include "JumpState.h"
#include "FallState.h"
#include "LandingState.h"
#include "RunJumpState.h"
#include "RunFallState.h"
#include "RunLandingState.h"
#include "RunJumpAttack1State.h"
#include "RunJumpAttack2State.h"
#include "RunJumpAttack3State.h"
#include "JumpAttack1State.h"
#include "Skill2_1State.h"
#include "JumpSkill2_1State.h"
#include "Skill3_1State.h"
#include "JumpSkill3_1State.h"
#include "DamageState.h"
#include "FlyDamageState.h"
#include "DownState.h"
#include "DeadState.h"
#include "EscapeState.h"




namespace Sample {

	/**
	 * @brief		ステート生成インターフェイス
	 */
	class PlayerStateCreator : public IStateCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~PlayerStateCreator() = default;

		/**
		 * @brief		生成
		 */
		bool Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input) override {
			stateMachine->AddState(State::Create<IdleState>(actor, input,
				IdleState::Parameter{
					5.0f
				
				}));
			stateMachine->AddState(State::Create<IdleMotionState>(actor, input));
			stateMachine->AddState(State::Create<MoveState>(actor, input));
			stateMachine->AddState(State::Create<JumpState>(actor, input));
			stateMachine->AddState(State::Create<FallState>(actor, input));
			stateMachine->AddState(State::Create<LandingState>(actor, input));
			stateMachine->AddState(State::Create<RunState>(actor, input));
			stateMachine->AddState(State::Create<RunJumpState>(actor, input));
			stateMachine->AddState(State::Create<RunFallState>(actor, input));
			stateMachine->AddState(State::Create<RunLandingState>(actor, input));
			stateMachine->AddState(State::Create<DamageState>(actor, input,
				DamageState::Parameter{
					1.0f
				}));
			stateMachine->AddState(State::Create<FlyDamageState>(actor, input));
			stateMachine->AddState(State::Create<DeadState>(actor, input));
			stateMachine->AddState(State::Create<DownState>(actor, input,
				DownState::Parameter{
					1.0f
				}));

			stateMachine->AddState(State::Create<Attack1State>(actor, input,
				Attack1State::Parameter{
					2
					,GameFrameTime * 25.0f
					,GameFrameTime * 42.0f
					,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.5f, 0, Vector3(0.3f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr ,2,Vector3(0.8f, 1.5f, 1.0f) }
					,EffectCreateParameter{ "Effect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f }

				}));

			stateMachine->AddState(State::Create<Attack2State>(actor, input,
				Attack2State::Parameter{
					2
					,GameFrameTime * 25.0f
					,GameFrameTime * 40.0f
					,ShotAABB{ Vector3(0.7f, 0.7f, 0), 1.0f, 0, Vector3(0.2f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr,2, Vector3(0.8f, 1.5f, 1.0f) }

				}));
			stateMachine->AddState(State::Create<Attack3State>(actor, input,
				Attack3State::Parameter{
					2
					,GameFrameTime * 25.0f
					,GameFrameTime * 55.0f
					,ShotAABB{ Vector3(0.7f, 0.7f, 0), 0.3f, 0, Vector3(0.3f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,2, Vector3(0.8f, 2.0f, 1.0f)}

				}));
			stateMachine->AddState(State::Create<RunAttack1State>(actor, input,
				RunAttack1State::Parameter{
					2
					,GameFrameTime * 20.0f
					,GameFrameTime * 40.0f
					,ShotAABB{ Vector3(0.7f, 0.8f, 0), 0.5f, 0, Vector3(0.4f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr,2, Vector3(1.2f, 1.5f, 0.8f) }
					,EffectCreateParameter{ "Effect2", Vector3(0.8f, 1.0f, 0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360.0f), 0.0f),2.0f }

				}));
			stateMachine->AddState(State::Create<JumpAttack1State>(actor, input,
				JumpAttack1State::Parameter{
					2
					,GameFrameTime * 20.0f
					,ShotAABB{ Vector3(0.7f, 0.8f, 0), 10.0f, 0, Vector3(0.1f, 0.0f, 0.0f),false,CHARA_PLAYER, nullptr,2, Vector3(1.0f, 1.2f, 1.0f) }
					,EffectCreateParameter{ "Effect2", Vector3(0.8f,1.0f,0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),2.0f }

				}));

			stateMachine->AddState(State::Create<RunJumpAttack1State>(actor, input,
				RunJumpAttack1State::Parameter{
					2
					,GameFrameTime * 15.0f
					,GameFrameTime * 22.0f
					,ShotAABB{ Vector3(0.8f, 0.7f, 0), 10.0f, 0, Vector3(0.3f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,2, Vector3(1.5f, 1.5f, 1.5f) }
					,EffectCreateParameter{ "Effect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f }

				}));
			stateMachine->AddState(State::Create<RunJumpAttack2State>(actor, input,
				RunJumpAttack2State::Parameter{
					2
					,GameFrameTime * 20.0f
					,ShotAABB{ Vector3(0.7f, 0.7f, 0), 10.0f, 0, Vector3(0.2f, 0.2f, 0.0f),true,CHARA_PLAYER, nullptr,2, Vector3(1.5f, 1.5f, 1.5f) }

				}));
			stateMachine->AddState(State::Create<RunJumpAttack3State>(actor, input,
				RunJumpAttack3State::Parameter{
					2
					,GameFrameTime * 12.0f
					,GameFrameTime * 40.0f
					,ShotAABB{ Vector3(0.7f, 1.2f, 0), 0.3f, 0, Vector3(0.3f, 0.15f, 0.0f),true,CHARA_PLAYER, nullptr,2, Vector3(1.5f, 2.0f, 1.5f) }

				}));

			stateMachine->AddState(State::Create<Skill1_1State>(actor, input,
				Skill1_1State::Parameter{
					4
					,GameFrameTime * 40.0f
					,GameFrameTime * 80.0f
					,ShotAABB{ Vector3(5.0f, 0.7f, 0), 0.05f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,4, Vector3(7.0f, 10.0f, 7.0f) }
					,EffectCreateParameter{ "Effect3", Vector3(0.8f, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.8f }

				}));
			stateMachine->AddState(State::Create<Skill2_1State>(actor, input,
				Skill2_1State::Parameter{
					3
					,GameFrameTime * 15.0f
					,GameFrameTime * 25.0f
					,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3, Vector3(5.0f, 2.0f, 2.0f) }
					,ShotSphere{ Vector3(0.7f, 0.7f, 0), 0.1f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3,2.0f }
					,EffectCreateParameter{ "Effect4", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f }

				}));
			stateMachine->AddState(State::Create<JumpSkill2_1State>(actor, input,
				JumpSkill2_1State::Parameter{
					3
					,GameFrameTime * 15.0f
					,GameFrameTime * 25.0f
					,ShotAABB{ Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3, Vector3(5.0f, 2.0f, 2.0f) }
					,ShotSphere{ Vector3(0.7f, 0.7f, 0), 0.1f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,3,2.0f }
					,EffectCreateParameter{ "Effect4", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f }

				}));
			stateMachine->AddState(State::Create<Skill3_1State>(actor, input,
				Skill3_1State::Parameter{
					3
					,GameFrameTime * 7.0f
					,3.5f
					,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.5f, 0.15f, 0.5f),false,CHARA_PLAYER, nullptr,3, Vector3(4.0f, 8.0f, 4.0f) }
					,EffectCreateParameter{ "Effect5", Vector3(0, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f }

				}));
			stateMachine->AddState(State::Create<JumpSkill3_1State>(actor, input,
				JumpSkill3_1State::Parameter{
					3
					,GameFrameTime * 7.0f
					,3.5f
					,ShotAABB{ Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.5f, 0.15f, 0.5f),false,CHARA_PLAYER,nullptr,3, Vector3(4.0f, 8.0f, 4.0f) }
					,EffectCreateParameter{ "Effect5", Vector3(0, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f }

				}));
			stateMachine->AddState(State::Create<EscapeState>(actor, input,
				EscapeState::Parameter{
					2
					,GameFrameTime * 5.0f
					,GameFrameTime * 35.0f
				}));

			return true;
		}
	};
}