#pragma once
#include "json.hpp"
#include "EnemyBuildParameter.h"
#include "EnemyBuilderDictionary.h"
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
		EnemyStatusDictionary Load(const std::string& name);
		/**
		 * @brief		生成
		 */
		EnemyStatusDictionary Load(nlohmann::json& os);
	};
}


