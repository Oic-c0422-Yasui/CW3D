#include "ZombieAICreator.h"

ActionGame::CharacterAIPtr ActionGame::ZombieAICreator::Create(const ActorPtr& actor,
																const StateMachinePtr& machine, 
																const Input::StateInputPtr& input)
{
	auto ai = std::make_shared<CharacterStateAI>(actor, machine, input, std::make_shared<AICycleFixed>(30));
	ai->AddStateAI(STATE_KEY_IDLE, CStateAI::Create<CIdleStateAI>(actor, machine, input,Vector3(5,1,4.5f), Vector3(1.5f,1.0f,1.0f),3));
	ai->AddStateAI(STATE_KEY_MOVE, CStateAI::Create<CMoveStateAI>(actor, machine, input, Vector3(5, 1, 4.5f), Vector3(1.5f, 1.0f, 1.0f), 3));
	ai->AddStateAI(STATE_KEY_ATTACK1, CStateAI::Create<CAttackStateAI>(actor, machine, input));
	ai->AddStateAI(STATE_KEY_ATTACK2, CStateAI::Create<CAttackStateAI>(actor, machine, input));
	ai->RegisterKey();
	return ai;
}
