#pragma once
#include "json.hpp"
#include "EnemyBuildParameter.h"
#include "GameDefine.h"


namespace Sample
{

	class JsonEnemyStatusLoader
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonEnemyStatusLoader();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		std::vector<EnemyBuildParameter> Load(const std::string& name);
		/**
		 * @brief		����
		 */
		std::vector<EnemyBuildParameter> Load(nlohmann::json& os);
	};
}


