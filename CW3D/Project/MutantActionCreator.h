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
	 * @brief		ミュータントアクション生成クラス
	 */
    class MutantActionCreator :  public IActionCreator
    {
		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr & actor) override;
    };
}


