#include "MutantAICreator.h"
#include	"CharacterStateAI.h"
#include	"MutantIdleStateAI.h"
#include	"MoveStateAI.h"
#include	"MutantMoveStateAI.h"
#include	"AttackStateAI.h"
#include	"AICycleTension.h"

ActionGame::CharacterAIPtr ActionGame::MutantAICreator::Create(const ActorPtr& actor,
																const StateMachinePtr& machine, 
																const Input::StateInputPtr& input)
{
	auto ai = std::make_shared<CharacterStateAI>(actor, machine, input, std::make_shared<AICycleTension>(actor));
	ai->AddStateAI(STATE_KEY_IDLE, CStateAI::Create<CMutantIdleStateAI>(actor, machine, input, 
										Vector3(12.0f, 5.0f, 4.5f), Vector3(4.0f, 5.0f, 2.0f),Vector3(8.0f, 5.0f, 2.5f),20,60,0.5f));
	ai->AddStateAI(STATE_KEY_MOVE, CStateAI::Create<CMutantMoveStateAI>(actor, machine, input,
										Vector3(6.0f, 5.0f, 5.0f), Vector3(4.0f, 5.0f, 2.0f), Vector3(8.0f, 5.0f, 2.5f),20, 60, 0.5f));
	ai->RegisterKey();
	return ai;
}
