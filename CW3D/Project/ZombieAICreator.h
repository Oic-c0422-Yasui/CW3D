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
	 * @brief		�]���rAI�����N���X
	 */
	class ZombieAICreator : public ICharacterAICreator
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CharacterAIPtr Create(const ActorPtr& actor,
			const StateMachinePtr& machine,
			const Input::StateInputPtr& input) override;
	};

	
}

