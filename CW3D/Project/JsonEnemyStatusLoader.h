#pragma once
#include "json.hpp"
#include "EnemyBuildParameter.h"
#include "EnemyBuilderDictionary.h"



namespace ActionGame
{

	class JsonEnemyStatusLoader
	{
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonEnemyStatusLoader();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		EnemyStatusDictionary Load(const std::string& name);
		/**
		 * @brief		����
		 */
		EnemyStatusDictionary Load(nlohmann::json& os);
	};
}


