#pragma once


#include	"json.hpp"
#include	"Division.h"
#include	"JsonEnemyCreator.h"
#include	"JsonObjectCreator.h"


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
		static DivisionArrayPtr Create(const std::string& name);
		/**
		 * @brief		生成
		 */
		static DivisionArrayPtr Create(nlohmann::json& os);
	};

}