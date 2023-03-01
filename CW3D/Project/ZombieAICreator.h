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
		 * @brief		コンストラクタ
		 */
		CharacterAIPtr Create(const ActorPtr& actor,
			const StateMachinePtr& machine,
			const Input::StateInputPtr& input) override;
	};

	
}

