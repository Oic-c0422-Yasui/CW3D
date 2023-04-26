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
#include "RunAttack2State.h"
#include "ShockWaveSkillState.h"
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
#include "BeamSkillState.h"
#include "JumpBeamSkillState.h"
#include "StormSkillState.h"
#include "JumpStormSkillState.h"
#include "DamageState.h"
#include "FlyDamageState.h"
#include "DownState.h"
#include "DeadState.h"
#include "EscapeState.h"
#include "ClearPoseState.h"
#include "DropKickSkillState.h"
#include "StartPoseState.h"
#include "FlyHighSkillState.h"



namespace ActionGame {

	/**
	 * @brief		ステート生成インターフェイス
	 */
	class PlayerStateCreator : public IStateCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		bool Create(const StateMachinePtr& stateMachine,
					const ActorPtr& actor,
					const Input::InputPtr& input) override;
			
	};
}