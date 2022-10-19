#pragma once

#include	"json.hpp"
#include	"JsonDivisionCreator.h"
#include	"StageBase.h"

namespace Sample 
{



class JsonStageCreator
{
private:

public:
	/**
		 * @brief		コンストラクタ
		 */
	JsonStageCreator();
	/**
	 * @brief		JSonファイルからの生成
	 */
	static StagePtr Create(const std::string& name);
	/**
	 * @brief		生成
	 */
	static StagePtr Create(nlohmann::json& os);
};

}