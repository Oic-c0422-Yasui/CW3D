#pragma once


#include	"json.hpp"
#include	"Division.h"
#include	"JsonEnemyLoader.h"
#include	"JsonObjectCreator.h"


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
		static DivisionArrayPtr Create(const std::string& name);
		/**
		 * @brief		����
		 */
		static DivisionArrayPtr Create(nlohmann::json& os);
	};

}