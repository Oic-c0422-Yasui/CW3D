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




namespace ActionGame {

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
		bool Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input) override;
	};
}