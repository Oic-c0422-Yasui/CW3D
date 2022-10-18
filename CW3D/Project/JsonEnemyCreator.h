#pragma once


#include	"json.hpp"
#include	"Enemy.h"
#include	"ZombieActionCreator.h"
#include	"ZombieStateCreator.h"


namespace Sample {
	class EnemyDictionary
	{
	public:
		struct Value
		{
			ActionCreatorPtr actionCreator;
			StateCreatorPtr stateCreator;
		};
	private:
		std::map<std::string, Value> dictionary;
	public:
		
		EnemyDictionary()
		{

			dictionary["Zombie"] = Value{ std::make_shared<ZombieActionCreator>(), std::make_shared<ZombieStateCreator>() };

		}
		Value& GetDictionary(std::string name)
		{
			assert(dictionary.find(name) != dictionary.end());
			return dictionary[name];
		}

	};


	class JsonEnemyCreator
	{
	private:
		EnemyDictionary dictionary;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonEnemyCreator();
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		std::vector<EnemyPtr> Create(const std::string& name);
		/**
		 * @brief		����
		 */
		std::vector<EnemyPtr> Create(nlohmann::json& os);
	};

}