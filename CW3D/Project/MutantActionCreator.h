#pragma once

#include "IActionCreator.h"
#include "Attack1Action.h"
#include "IdleAction.h"
#include "MoveAction.h"
#include "DeadState.h"
#include "DamageState.h"
#include "FlyDamageState.h"
#include "NPCStartPoseAction.h"

namespace ActionGame
{
	/**
	 * @brief		�~���[�^���g�A�N�V���������N���X
	 */
    class MutantActionCreator :  public IActionCreator
    {
		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr & actor) override;
    };
}


