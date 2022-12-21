#include "JsonEnemyBuildParameterLoader.h"


using namespace ActionGame;

ActionGame::JsonEnemyBuildParameterLoader::JsonEnemyBuildParameterLoader()
	: m_Spawners(std::make_shared<Spawner::EnemySpawnerArray>())
{
}

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
		
		//敵のスポナー取得
		Spawner::JsonSpawnerCreator spawnerCreator;
		auto spawner = spawnerCreator.Create(enemy["Spawner"]);
		m_Spawners->push_back(spawner);
		
		EnemyParam param(type,pos);
		
		EnemyStatusPtr status = statusDictionary.Get(type);


		parameter->push_back(std::make_shared<EnemyBuildParameter>(param,status));
	}


	return parameter;
}

const Spawner::EnemySpawnerArrayPtr& ActionGame::JsonEnemyBuildParameterLoader::GetSpawner()
{
	return m_Spawners;
}
