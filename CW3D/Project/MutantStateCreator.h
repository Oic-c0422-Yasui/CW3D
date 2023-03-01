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
	 * @brief		�~���[�^���g�X�e�[�g����
	 */
    class MutantStateCreator : public IStateCreator
    {
		/**
		 * @brief		����
		 */
		bool Create(const StateMachinePtr & stateMachine, 
					const ActorPtr & actor, 
					const Input::InputPtr & input) override;
    };

}


