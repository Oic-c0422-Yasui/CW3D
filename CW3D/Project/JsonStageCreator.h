#pragma once

#include	"json.hpp"
#include	"JsonStageLoader.h"
#include	"JsonDivisionCreator.h"
#include	"JsonEnemyLoader.h"
#include	"StageBase.h"

namespace Sample 
{



class JsonStageCreator
{
private:

public:
	/**
		 * @brief		�R���X�g���N�^
		 */
	JsonStageCreator();
	/**
	 * @brief		JSon�t�@�C������̐���
	 */
	static StagePtr Create(const std::string& name);
	/**
	 * @brief		����
	 */
	static StagePtr Create(nlohmann::json& os);
};

}