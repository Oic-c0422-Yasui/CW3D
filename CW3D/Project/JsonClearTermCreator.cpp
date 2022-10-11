#include "JsonClearTermCreator.h"

using namespace Sample;

JsonClearTermCreator::JsonClearTermCreator()
{
}

std::vector<ClearTermPtr> JsonClearTermCreator::Create(const std::string& name)
{
	return std::vector<ClearTermPtr>();
}

std::vector<ClearTermPtr> JsonClearTermCreator::Create(nlohmann::json& os)
{

	return std::vector<ClearTermPtr>();
}
