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
		static std::vector<ObjectPtr> Create(const std::string& name);
		/**
		 * @brief		����
		 */
		static std::vector<ObjectPtr> Create(nlohmann::json& os);
	};

}