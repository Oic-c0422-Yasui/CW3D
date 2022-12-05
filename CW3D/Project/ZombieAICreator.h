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
	 * @brief		AI生成クラス
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
		CharacterAIPtr Create(const ActorPtr& actor, const StateMachinePtr& machine,
			const StateInputPtr& input) override {
			auto ai = std::make_shared<CharacterStateAI>(actor, machine, input, std::make_shared<AICycleFixed>(30));
			ai->AddStateAI(STATE_KEY_IDLE, StateAI::Create<IdleStateAI>(actor, machine, input));
			ai->AddStateAI(STATE_KEY_MOVE, StateAI::Create<MoveStateAI>(actor, machine, input));
			ai->AddStateAI(STATE_KEY_ATTACK1, StateAI::Create<AttackStateAI>(actor, machine, input));
			ai->AddStateAI(STATE_KEY_ATTACK2, StateAI::Create<AttackStateAI>(actor, machine, input));
			ai->RegisterKey();
			return ai;
		}
	};
}

