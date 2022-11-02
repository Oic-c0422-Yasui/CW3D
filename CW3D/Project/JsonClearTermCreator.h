#pragma once


#include	"json.hpp"

#include	"IClearTerm.h"


namespace Sample {
	

	class JsonClearTermCreator
	{
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonClearTermCreator();
		/**
		 * @brief		JSonファイルからの生成
		 */
		std::vector<ClearTermPtr> Create(const std::string& name);
		/**
		 * @brief		生成
		 */
		std::vector<ClearTermPtr> Create(nlohmann::json& os);
	};
}
