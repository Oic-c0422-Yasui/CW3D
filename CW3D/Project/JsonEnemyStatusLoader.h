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
		 * @brief		コンストラクタ
		 */
		JsonEnemyStatusLoader();
		/**
		 * @brief		JSonファイルからの生成
		 */
		EnemyStatusDictionary Load(const std::string& name);
		/**
		 * @brief		生成
		 */
		EnemyStatusDictionary Load(nlohmann::json& os);
	};
}


