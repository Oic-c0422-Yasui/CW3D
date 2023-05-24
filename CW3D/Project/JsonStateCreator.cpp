#include "JsonStateCreator.h"

ActionGame::JsonStateCreator::JsonStateCreator()
{
}

bool ActionGame::JsonStateCreator::Load(const std::string& fileName)
{
	std::ifstream ifs(fileName);
	if (ifs.fail())
	{
		return false;
	}
	data_ = nlohmann::json::parse(ifs);
    return true;
}

bool ActionGame::JsonStateCreator::Create(const StateMachinePtr& stateMachine, const ActorPtr& actor, const Input::InputPtr& input)
{

	return true;
}


