#pragma once
#include	"json.hpp"
#include	"JsonDivisionCreator.h"


namespace Sample
{
	class JsonStageLoader
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonStageLoader();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		bool Load(const std::string& name);
		/**
		 * @brief		����
		 */
		bool Load(nlohmann::json& os);
	};

}


