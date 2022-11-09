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
		 * @brief		�R���X�g���N�^
		 */
		JsonDivisionCreator();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		DivisionArrayPtr Create(const std::string& name,EnemyStatusDictionary status);
		/**
		 * @brief		����
		 */
		DivisionArrayPtr Create(nlohmann::json& os, EnemyStatusDictionary status);
	};

}