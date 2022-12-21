#pragma once
#include "EnemySpawner.h"
#include "json.hpp"


namespace Spawner
{
	class SpawnerBuilder
	{
	private:

	public:
		virtual ~SpawnerBuilder() = default;

		virtual EnemySpawnerPtr Create(nlohmann::json& os) = 0;
		virtual EnemySpawnerPtr Create() = 0;
	};
	using SpawnerBuilderPtr = std::shared_ptr<SpawnerBuilder>;
}

