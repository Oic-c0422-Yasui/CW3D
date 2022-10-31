#include "JsonEnemyLoader.h"

using namespace Sample;

std::vector<EnemyBuildParameter> Sample::JsonEnemyLoader::Load(const std::string& name, EnemyStatusDictionary statusDictionary)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return std::vector<EnemyBuildParameter>();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os, statusDictionary);
}

std::vector<EnemyBuildParameter> Sample::JsonEnemyLoader::Load(nlohmann::json& os,EnemyStatusDictionary statusDictionary)
{
	auto& Enemys = os["Enemys"];

	std::vector<EnemyBuildParameter> parameter;

	for (auto& enemy : Enemys)
	{
		
		Vector3 pos;
		std::string type;

		enemy["PosX"].get_to(pos.x);
		enemy["PosY"].get_to(pos.y);
		enemy["PosZ"].get_to(pos.z);
		enemy["Type"].get_to(type);
		
		EnemyParam param(type,pos);
		
		EnemyStatusPtr status = statusDictionary.Get(type);

		parameter.push_back(EnemyBuildParameter(param,status));
	}


	return parameter;
}
