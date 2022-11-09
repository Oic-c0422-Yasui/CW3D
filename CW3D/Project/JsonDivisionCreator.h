#pragma once


#include	"json.hpp"
#include	"Division.h"
#include	"JsonEnemyBuildParameterLoader.h"
#include	"JsonObjectCreator.h"
#include	"JsonClearTermCreator.h"


namespace Sample {


	class JsonDivisionCreator
	{
	private:
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonDivisionCreator();
		/**
		 * @brief		JSonファイルからの生成
		 */
		DivisionArrayPtr Create(const std::string& name,EnemyStatusDictionary status);
		/**
		 * @brief		生成
		 */
		DivisionArrayPtr Create(nlohmann::json& os, EnemyStatusDictionary status);
	};

}