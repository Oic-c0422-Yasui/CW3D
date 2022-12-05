#include "JsonClearTermCreator.h"

using namespace ActionGame;

JsonClearTermCreator::JsonClearTermCreator()
	:dictionary()
{
}

ClearTermArray JsonClearTermCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return ClearTermArray();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

ClearTermArray JsonClearTermCreator::Create(nlohmann::json& os)
{
	ClearTermArray	ClearTerms;
	for (auto& str : os)
	{
		auto& type = str["Type"];

		std::string typeName;
		type["Name"].get_to(typeName);

		auto& dicValue = dictionary.Get(typeName);

		ClearTermPtr clearTerm;
		clearTerm = dicValue->Create(type);
		ClearTerms.push_back(clearTerm);
	}
	return ClearTerms;
}
