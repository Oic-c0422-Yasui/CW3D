#pragma once


#include	"json.hpp"
#include	"Enemy.h"
#include	"ZombieActionCreator.h"
#include	"ZombieStateCreator.h"
#include	"ZombieParameterCreator.h"
#include	"ZombieAICreator.h"
#include	"EnemyBuilder.h"


namespace Sample {
	class EnemyDictionary
	{
	public:
		struct Value
		{
			ActionCreatorPtr actionCreator;
			StateCreatorPtr stateCreator;
			ParameterCreatorPtr parameterCreator;
			CharacterAICreatorPtr aiCreator;
		};
	private:
		std::map<std::string, Value> dictionary;
	public:
		
		EnemyDictionary()
		{

			dictionary["Zombie"] = Value{	std::make_shared<ZombieActionCreator>(),
											std::make_shared<ZombieStateCreator>(),
											std::make_shared<ZombieParameterCreator>(),
											std::make_shared<ZombieAICreator>()};

		}
		const Value& GetDictionary(std::string name)
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
		EnemyArrayPtr Create(const std::string& name);
		/**
		 * @brief		����
		 */
		EnemyArrayPtr Create(nlohmann::json& os);
	};

}