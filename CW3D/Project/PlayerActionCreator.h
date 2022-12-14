#pragma once

#include	"IActionCreator.h"
#include	"IdleAction.h"
#include	"MoveAction.h"
#include	"JumpAction.h"
#include	"FallAction.h"
#include	"LandingAction.h"
#include	"Attack1Action.h"
#include	"Attack2Action.h"
#include	"Attack3Action.h"


#include	"RunAction.h"
#include	"IdleMotionAction.h"

#include	"RunAttack1Action.h"
#include	"ShockWaveSkillAction.h"

#include	"RunJumpAction.h"
#include	"RunFallAction.h"
#include	"RunLandingAction.h"
#include	"RunJumpAttack1Action.h"
#include	"RunJumpAttack2Action.h"
#include	"RunJumpAttack3Action.h"
#include	"JumpAttack1Action.h"
#include	"BeamSkillAction.h"
#include	"JumpBeamSkillAction.h"
#include	"StormSkillAction.h"
#include	"JumpStormSkillAction.h"
#include	"FlyDamageAction.h"
#include	"DownAction.h"

#include	"DamageAction.h"
#include	"DeadAction.h"
#include	"EscapeAction.h"
#include	"ClearPoseAction.h"
#include	"DropKickSkillAction.h"
#include	"StartPoseAction.h"


namespace ActionGame {
	/**
	 * @brief		アクション生成インターフェイス
	 */
	class PlayerActionCreator : public IActionCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~PlayerActionCreator() = default;


		/**
		 * @brief		生成
		 */
		bool Create(const ActorPtr& actor) override;
	};
}