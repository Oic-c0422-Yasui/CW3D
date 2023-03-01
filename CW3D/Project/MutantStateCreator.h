#pragma once

#include "IStateCreator.h"
#include "IdleState.h"
#include "MoveState.h"
#include "Attack1State.h"
#include "DeadState.h"
#include "DamageState.h"
#include "NPCCameraStartPoseState.h"

namespace ActionGame
{
	/**
	 * @brief		ミュータントステート生成
	 */
    class MutantStateCreator : public IStateCreator
    {
		/**
		 * @brief		生成
		 */
		bool Create(const StateMachinePtr & stateMachine, 
					const ActorPtr & actor, 
					const Input::InputPtr & input) override;
    };

}


