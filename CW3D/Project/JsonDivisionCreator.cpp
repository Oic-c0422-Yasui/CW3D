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
	DivisionArrayPtr JsonDivisionCreator::Create(const std::string& name) {
		std::ifstream ifs(name);
		if (ifs.fail())
		{
			return DivisionArrayPtr();
		}
		nlohmann::json os = nlohmann::json::parse(ifs);
		return Create(os);
	}



	

	/**
	 * @brief		生成
	 */
	DivisionArrayPtr JsonDivisionCreator::Create(nlohmann::json& os) {
		DivisionArray divArray;
		auto& divisions = os["Divisions"];
		for (auto& division : divisions)
		{
			CDivision::DIVISION_DATA data{};

			//クリア条件生成
			

			//敵生成
			JsonEnemyCreator enemyCreator;
			data.Enemys = enemyCreator.Create(division["Enemys"]);
			data.EnemyCount = data.Enemys.size();

			//オブジェクト生成
			JsonObjectCreator objectCreator;
			data.Objects = objectCreator.Create(division["Objects"]);
			data.ObjectCount = data.Objects.size();

			divArray.push_back(std::make_shared<CDivision>(data));
		}
		DivisionArrayPtr result = std::make_shared<DivisionArray>(divArray);
		return result;
	}

