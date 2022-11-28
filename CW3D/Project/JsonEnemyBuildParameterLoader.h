#pragma once
#include "json.hpp"
#include "EnemyBuildParameter.h"
#include "JsonEnemyStatusLoader.h"

namespace Sample
{
	class JsonEnemyBuildParameterLoader
	{
	public:
		EnemyBuildParameterArrayPtr Load(const std::string& name, EnemyStatusDictionary statusDictionary);
		EnemyBuildParameterArrayPtr Load(nlohmann::json& os,EnemyStatusDictionary statusDictionary);
	};

}


