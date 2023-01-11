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
		 * @brief		�R���X�g���N�^
		 */
		JsonClearTermCreator();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		ClearTermArray Create(const std::string& name);
		/**
		 * @brief		����
		 */
		ClearTermArray Create(nlohmann::json& os);
	};
}
