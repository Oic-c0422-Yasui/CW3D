#include "MutantAICreator.h"

ActionGame::CharacterAIPtr ActionGame::MutantAICreator::Create(const ActorPtr& actor,
																const StateMachinePtr& machine, 
																const Input::StateInputPtr& input)
{
	auto ai = std::make_shared<CharacterStateAI>(actor, machine, input, std::make_shared<AICycleTension>(actor));
	ai->AddStateAI(STATE_KEY_IDLE, CStateAI::Create<CIdleStateAI>(actor, machine, input, Vector3(5, 5.0f, 4.5f), Vector3(2.0f, 5.0f, 2.0f),20));
	ai->AddStateAI(STATE_KEY_MOVE, CStateAI::Create<CMoveStateAI>(actor, machine, input, Vector3(6, 5.0f, 5.0f), Vector3(2.0f, 5.0f, 2.0f),20));
	//ai->AddStateAI(STATE_KEY_ATTACK1, CStateAI::Create<CAttackStateAI>(actor, machine, input));
	ai->RegisterKey();
	return ai;
}
