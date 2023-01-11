#pragma once

#include <fstream>
#include	"json.hpp"

#include	"IClearTerm.h"
#include	"ClearTermBuilderDictionary.h"


namespace ActionGame {
	

	class JsonClearTermCreator
	{
	private:
		ClearTermBuilderDictionary dictionary;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		JsonClearTermCreator();
		/**
		 * @brief		JSonファイルからの生成
		 */
		ClearTermArray Create(const std::string& name);
		/**
		 * @brief		生成
		 */
		ClearTermArray Create(nlohmann::json& os);
	};
}
