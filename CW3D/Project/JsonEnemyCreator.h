#pragma once


#include	"json.hpp"
#include	"StageBase.h"
#include	"Division.h"
#include	"DivisionObject.h"
#include	"ZombieActionCreator.h"
#include	"ZombieStateCreator.h"


namespace Sample {
	class EnemyDictionary
	{
		struct Value
		{
			std::shared_ptr<IActionCreator> actionCreator;
			std::shared_ptr<IStateCreator> stateCreator;
		};
		std::map<std::string, Value> dic;
		EnemyDictionary()
		{
			dic["Zombie"] = Value{ std::make_shared<ZombieActionCreator>, std::make_shared<ZombieStateCreator>() };
		}

	};
	class JsonEnemyCreator
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonEnemyCreator();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		static std::vector<EnemyPtr> Create(const std::string& name);
		/**
		 * @brief		����
		 */
		static std::vector<EnemyPtr> Create(nlohmann::json& os);
	};

}