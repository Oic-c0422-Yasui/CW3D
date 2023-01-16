#pragma once
#include "ICharacterAICreator.h"
#include	"CharacterStateAI.h"
#include	"IdleStateAI.h"
#include	"MoveStateAI.h"
#include	"AttackStateAI.h"
#include	"AICycleTension.h"

namespace ActionGame
{
    class MutantAICreator : public ICharacterAICreator
    {
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~MutantAICreator() = default;

		/**
		 * @brief		コンストラクタ
		 */
		CharacterAIPtr Create(const ActorPtr & actor,
			const StateMachinePtr & machine,
			const StateInputPtr & input) override;
    };
}


