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

	auto& stageMesh = os["StageMesh"];

	auto& enemyStatusFile = os["EnemyStatusFile"];


	

	DivisionArray divArray;

	std::vector<EnemyPtr>	Enemys;

	
	return StagePtr();
}
