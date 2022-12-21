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
		 * @brief		�R���X�g���N�^
		 */
		JsonSpawnerCreator();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		EnemySpawnerPtr Create(const std::string& name);
		/**
		 * @brief		����
		 */
		EnemySpawnerPtr Create(nlohmann::json& os);
	};

}


