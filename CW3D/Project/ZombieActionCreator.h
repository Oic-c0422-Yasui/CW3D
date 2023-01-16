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
	 * @brief		ゾンビアクション生成クラス
	 */
	class ZombieActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ZombieActionCreator() = default;

		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr& actor) override;
	};
}