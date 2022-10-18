#pragma once


#include	"json.hpp"

#include	"DivisionObject.h"


namespace Sample {
	class JsonObjectCreator
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonObjectCreator();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		std::vector<ObjectPtr> Create(const std::string& name);
		/**
		 * @brief		����
		 */
		std::vector<ObjectPtr> Create(nlohmann::json& os);
	};

}