#pragma once
#include "json.hpp"
#include "EnemyBuildParameter.h"
#include "JsonEnemyStatusLoader.h"

namespace Sample
{
	class JsonEnemyLoader
	{
	public:
		std::vector<EnemyBuildParameter> Load(const std::string& name);
		std::vector<EnemyBuildParameter> Load(nlohmann::json& os,EnemyStatusDictionary status);
	};

}

