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
	 * @brief		�X�e�[�g�����C���^�[�t�F�C�X
	 */
	class ZombieStateCreator : public IStateCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ZombieStateCreator() = default;

		/**
		 * @brief		����
		 */
		bool Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const InputPtr& input) override;
	};
}