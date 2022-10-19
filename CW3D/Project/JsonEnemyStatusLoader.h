#pragma once
#include "json.hpp"
#include "EnemyBuildParameter.h"
#include "GameDefine.h"


namespace Sample
{

	class JsonEnemyStatusLoader
	{
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonEnemyStatusLoader();
		/**
		 * @brief		JSonファイルからの生成
		 */
		std::vector<EnemyBuildParameter> Load(const std::string& name);
		/**
		 * @brief		生成
		 */
		std::vector<EnemyBuildParameter> Load(nlohmann::json& os);
	};
}


