#pragma once

#include	"IStateCreator.h"
#include "IdleState.h"
#include "MoveState.h"
#include "Attack1State.h"
#include "Attack2State.h"

#include "DamageState.h"
#include "FlyDamageState.h"
#include "DownState.h"
#include "DeadState.h"
#include "NPCStartPoseState.h"




namespace ActionGame {

	/**
	 * @brief		ゾンビステート生成
	 */
	class ZombieStateCreator : public IStateCreator
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