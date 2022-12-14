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


namespace ActionGame {
	/**
	 * @brief		�A�N�V���������C���^�[�t�F�C�X
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