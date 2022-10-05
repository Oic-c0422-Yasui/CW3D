#pragma once


#include	"json.hpp"
#include	"StageBase.h"
#include	"Division.h"
#include	"DivisionObject.h"
#include	"ZombieActionCreator.h"
#include	"ZombieStateCreator.h"

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
namespace Sample {
	class JsonEnemyCreator
	{
	private:

	public:
		/**
		 * @brief		JSonファイルからの生成
		 */
		static std::vector<EnemyPtr> Create(const std::string& name) {
			std::ifstream ifs(name);
			if (ifs.fail())
			{
				return std::vector<EnemyPtr>();
			}
			nlohmann::json os = nlohmann::json::parse(ifs);
			return Create(os);
		}



		/**
		 * @brief		コンストラクタ
		 */
		JsonEnemyCreator()
		{

		}

		/**
		 * @brief		生成
		 */
		static std::vector<EnemyPtr> Create(nlohmann::json& os) {
			std::vector<EnemyPtr>	Enemys;
			for (auto& enemy : os)
			{
				EnemyPtr ene;
				CVector3 pos;
				enemy["PosX"].get_to(pos.x);
				enemy["PosY"].get_to(pos.y);
				enemy["PosZ"].get_to(pos.z);
				auto& dicValue = dic[type];
				ene = std::make_shared<CEnemy>(pos, dicValue.actionCreator, dicValue.stateCreator);
				Enemys.push_back(ene);
			}
			return Enemys;
		}
	};

}