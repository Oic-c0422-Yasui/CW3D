#include "JsonEnemyStatusLoader.h"

using namespace Sample;

JsonEnemyStatusLoader::JsonEnemyStatusLoader()
{
}

std::vector<EnemyBuildParameter> JsonEnemyStatusLoader::Load(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return std::vector<EnemyBuildParameter>();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os);
}

std::vector<EnemyBuildParameter> JsonEnemyStatusLoader::Load(nlohmann::json& os)
{
	auto& Status = os["Status"];
	std::vector<EnemyBuildParameter> parameter;

	for (auto& status : Status)
	{
		int hp;
		float ultGauge;
		int attack;
		std::string meshName;

		status["HP"].get_to(hp);
		status["UltGauge"].get_to(ultGauge);
		status["ATK"].get_to(attack);
		status["Mesh"].get_to(meshName);

		parameter.push_back(EnemyBuildParameter(hp, ultGauge, attack, meshName));
	}
	

	return parameter;
}
