#include "MutantAICreator.h"

ActionGame::CharacterAIPtr ActionGame::MutantAICreator::Create(const ActorPtr& actor, const StateMachinePtr& machine, const StateInputPtr& input)
{
	auto ai = std::make_shared<CharacterStateAI>(actor, machine, input, std::make_shared<AICycleTension>(actor));
	ai->AddStateAI(STATE_KEY_IDLE, StateAI::Create<IdleStateAI>(actor, machine, input, Vector3(5, 1.5f, 4.5f), Vector3(2.0f, 1.0f, 2.0f),20));
	ai->AddStateAI(STATE_KEY_MOVE, StateAI::Create<MoveStateAI>(actor, machine, input, Vector3(6, 1.5f, 5.0f), Vector3(2.0f, 1.0f, 2.0f),20));
	//ai->AddStateAI(STATE_KEY_ATTACK1, StateAI::Create<AttackStateAI>(actor, machine, input));
	ai->RegisterKey();
	return ai;
}
