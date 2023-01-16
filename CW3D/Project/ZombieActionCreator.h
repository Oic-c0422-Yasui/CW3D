#pragma once

#include	"IActionCreator.h"
#include	"IdleAction.h"
#include	"MoveAction.h"

#include	"Attack1Action.h"
#include	"Attack2Action.h"

#include	"FlyDamageAction.h"
#include	"DownAction.h"

#include	"DamageAction.h"
#include	"DeadAction.h"
#include	"NPCStartPoseAction.h"


namespace ActionGame {
	/**
	 * @brief		�]���r�A�N�V���������N���X
	 */
	class ZombieActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ZombieActionCreator() = default;

		/**
		 * @brief		����
		 */
		bool Create(const ActorPtr& actor) override;
	};
}