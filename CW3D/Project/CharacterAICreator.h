#pragma once

#include	"ICharacterAICreator.h"
#include	"CharacterStateAI.h"
#include	"IdleStateAI.h"
#include	"MoveStateAI.h"
#include	"AICycleFixed.h"

namespace Sample
{
	/**
	 * @brief		AI生成クラス
	 */
	class CharacterAICreator : public ICharacterAICreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~CharacterAICreator() = default;

		/**
		 * @brief		コンストラクタ
		 */
		CharacterAIPtr Create(const ActorPtr& actor, const StateMachinePtr& machine,
			const StateInputPtr& input) override {
			auto ai = std::make_shared<CharacterStateAI>(actor, machine, input, std::make_shared<AICycleFixed>(30));
			ai->AddStateAI(STATE_KEY_IDLE, StateAI::Create<IdleStateAI>(actor, machine, input));
			ai->AddStateAI(STATE_KEY_MOVE, StateAI::Create<MoveStateAI>(actor, machine, input));
			ai->RegisterKey();
			return ai;
		}
	};
}

