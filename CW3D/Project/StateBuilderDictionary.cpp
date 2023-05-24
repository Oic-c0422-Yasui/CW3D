#include "StateBuilderDictionary.h"
#include "StateDefine.h"
#include "IdleStateBuilder.h"

ActionGame::StateBuilderDictionary::StateBuilderDictionary()
{
	dictionary_[STATE_KEY_IDLE] = std::make_shared<IdleStateBuilder>();
}

ActionGame::StateBuilderDictionary::~StateBuilderDictionary()
{
}
