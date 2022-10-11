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
	static std::vector<ClearTermPtr> Create(const std::string& name);
	/**
	 * @brief		����
	 */
	static std::vector<ClearTermPtr> Create(nlohmann::json& os);
};
}
