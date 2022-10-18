#pragma once


#include	"json.hpp"

#include	"DivisionObject.h"


namespace Sample {
	class JsonObjectCreator
	{
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonObjectCreator();
		/**
		 * @brief		JSonファイルからの生成
		 */
		std::vector<ObjectPtr> Create(const std::string& name);
		/**
		 * @brief		生成
		 */
		std::vector<ObjectPtr> Create(nlohmann::json& os);
	};

}