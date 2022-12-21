#pragma once
#include "json.hpp"
#include "EnemyBuildParameter.h"
#include "JsonEnemyStatusLoader.h"
#include "JsonSpawnerCreator.h"

namespace ActionGame
{
	class JsonEnemyBuildParameterLoader
	{
	private:
		Spawner::EnemySpawnerArrayPtr m_Spawners;
	public:
		JsonEnemyBuildParameterLoader();
		EnemyBuildParameterArrayPtr Load(const std::string& name, EnemyStatusDictionary statusDictionary);
		EnemyBuildParameterArrayPtr Load(nlohmann::json& os,EnemyStatusDictionary statusDictionary);

		const Spawner::EnemySpawnerArrayPtr& GetSpawner();
	};

}


