#include "StageCreator.h"

using namespace Sample;

Sample::StageCreator::StageCreator()
{
}

StagePtr Sample::StageCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return StagePtr();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

StagePtr Sample::StageCreator::Create(nlohmann::json& os)
{


	DivisionArray divArray;

	std::vector<EnemyPtr>	Enemys;

	
	return StagePtr();
}
