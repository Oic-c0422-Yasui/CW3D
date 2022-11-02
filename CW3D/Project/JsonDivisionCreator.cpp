#include	"JsonDivisionCreator.h"


using namespace Sample;

	/**
	 * @brief		コンストラクタ
	 */
	JsonDivisionCreator::JsonDivisionCreator()
	{
	
	}

	/**
	 * @brief		JSonファイルからの生成
	 */
	DivisionArrayPtr JsonDivisionCreator::Create(const std::string& name, EnemyStatusDictionary status) {
		std::ifstream ifs(name);
		if (ifs.fail())
		{
			return DivisionArrayPtr();
		}
		nlohmann::json os = nlohmann::json::parse(ifs);
		return Create(os,status);
	}



	

	/**
	 * @brief		生成
	 */
	DivisionArrayPtr JsonDivisionCreator::Create(nlohmann::json& os, EnemyStatusDictionary status) {
		DivisionArray divArray;
		auto& divisions = os["Divisions"];
		for (auto& division : divisions)
		{
			CDivision::DIVISION_DATA data{};

			//クリア条件生成
			JsonClearTermCreator 

			//敵生成
			JsonEnemyLoader enemyLoader;

			data.EnemysParam = enemyLoader.Load(division["Enemys"], status);
			data.EnemyCount = data.EnemysParam.size();

			//オブジェクト生成
			JsonObjectCreator objectCreator;
			data.Objects = objectCreator.Create(division["Objects"]);
			data.ObjectCount = data.Objects.size();

			divArray.push_back(std::make_shared<CDivision>(data));
		}
		DivisionArrayPtr result = std::make_shared<DivisionArray>(divArray);
		return result;
	}

