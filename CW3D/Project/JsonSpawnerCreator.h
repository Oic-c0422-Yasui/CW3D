#pragma once
#include "json.hpp"
#include "EnemySpawner.h"


namespace Spawner
{
	class JsonSpawnerCreator
	{
	private:
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonSpawnerCreator();
		/**
		 * @brief		JSonファイルからの生成
		 */
		EnemySpawnerPtr Create(const std::string& name);
		/**
		 * @brief		生成
		 */
		EnemySpawnerPtr Create(nlohmann::json& os);
	};

}


