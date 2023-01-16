#pragma once

#include	"ICharacterAICreator.h"

#include	"CharacterStateAI.h"
#include	"IdleStateAI.h"
#include	"MoveStateAI.h"
#include	"AttackStateAI.h"
#include	"AICycleFixed.h"

namespace ActionGame
{
	/**
	 * @brief		ゾンビAI生成クラス
	 */
	class ZombieAICreator : public ICharacterAICreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~ZombieAICreator() = default;

		/**
		 * @brief		コンストラクタ
		 */
		CharacterAIPtr Create(const ActorPtr& actor,
			const StateMachinePtr& machine,
			const StateInputPtr& input) override;
	};

	
}

