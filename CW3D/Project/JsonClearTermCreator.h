#pragma once


#include	"json.hpp"

#include	"IClearTerm.h"


namespace Sample {
	

	class JsonClearTermCreator
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonClearTermCreator();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		std::vector<ClearTermPtr> Create(const std::string& name);
		/**
		 * @brief		����
		 */
		std::vector<ClearTermPtr> Create(nlohmann::json& os);
	};
}
