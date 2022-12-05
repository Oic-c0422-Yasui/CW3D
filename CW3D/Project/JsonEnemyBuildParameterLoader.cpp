#include "JsonEnemyBuildParameterLoader.h"

using namespace ActionGame;

EnemyBuildParameterArrayPtr ActionGame::JsonEnemyBuildParameterLoader::Load(const std::string& name, EnemyStatusDictionary statusDictionary)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return EnemyBuildParameterArrayPtr();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os, statusDictionary);
}

EnemyBuildParameterArrayPtr ActionGame::JsonEnemyBuildParameterLoader::Load(nlohmann::json& os,EnemyStatusDictionary statusDictionary)
{

	EnemyBuildParameterArrayPtr parameter = std::make_shared<EnemyBuildParameterArray>();

	for (auto& enemy : os)
	{
		
		Vector3 pos;
		std::string type;

		enemy["PosX"].get_to(pos.x);
		enemy["PosY"].get_to(pos.y);
		enemy["PosZ"].get_to(pos.z);
		enemy["Type"].get_to(type);
		
		EnemyParam param(type,pos);
		
		EnemyStatusPtr status = statusDictionary.Get(type);

		parameter->push_back(std::make_shared<EnemyBuildParameter>(param,status));
	}


	return parameter;
}
