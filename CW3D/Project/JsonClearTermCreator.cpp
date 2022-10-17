#include "JsonClearTermCreator.h"

using namespace Sample;

JsonClearTermCreator::JsonClearTermCreator()
{
}

std::vector<ClearTermPtr> JsonClearTermCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return std::vector<ClearTermPtr>();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

std::vector<ClearTermPtr> JsonClearTermCreator::Create(nlohmann::json& os)
{

	return std::vector<ClearTermPtr>();
}
