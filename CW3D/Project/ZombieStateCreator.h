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
	 * @brief		�]���r�X�e�[�g����
	 */
	class ZombieStateCreator : public IStateCreator
	{
	public:

		/**
		 * @brief		����
		 */
		bool Create(const StateMachinePtr& stateMachine, 
					const ActorPtr& actor, 
					const Input::InputPtr& input) override;
	};
}