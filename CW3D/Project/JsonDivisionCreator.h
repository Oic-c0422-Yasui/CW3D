#pragma once



#include	"Division.h"
#include	"JsonEnemyBuildParameterLoader.h"
#include	"JsonObjectCreator.h"
#include	"JsonClearTermCreator.h"


namespace ActionGame {


	class JsonDivisionCreator
	{
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