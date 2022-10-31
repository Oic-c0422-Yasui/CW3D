#include "JsonStageCreator.h"

using namespace Sample;

Sample::JsonStageCreator::JsonStageCreator()
{
}

StagePtr Sample::JsonStageCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return StagePtr();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

StagePtr Sample::JsonStageCreator::Create(nlohmann::json& os)
{



	auto& enemyStatusFile = os["EnemyStatusFile"];
	JsonEnemyStatusLoader statusLoader;
	auto& enemyStatusDictionary = statusLoader.Load(enemyStatusFile);


	DivisionArray divArray;

	std::vector<EnemyPtr>	Enemys;

	
	return StagePtr();
}
