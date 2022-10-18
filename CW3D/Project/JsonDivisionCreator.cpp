#include	"JsonDivisionCreator.h"


using namespace Sample;

	/**
	 * @brief		�R���X�g���N�^
	 */
	JsonDivisionCreator::JsonDivisionCreator()
	{
	
	}

	/**
	 * @brief		JSon�t�@�C������̐���
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
	 * @brief		����
	 */
	DivisionArrayPtr JsonDivisionCreator::Create(nlohmann::json& os) {
		DivisionArray divArray;
		auto& divisions = os["Divisions"];
		for (auto& division : divisions)
		{
			CDivision::DIVISION_DATA data{};

			//�N���A��������
			

			//�G����
			JsonEnemyCreator enemyCreator;
			data.Enemys = enemyCreator.Create(division["Enemys"]);
			data.EnemyCount = data.Enemys.size();

			//�I�u�W�F�N�g����
			JsonObjectCreator objectCreator;
			data.Objects = objectCreator.Create(division["Objects"]);
			data.ObjectCount = data.Objects.size();

			divArray.push_back(std::make_shared<CDivision>(data));
		}
		DivisionArrayPtr result = std::make_shared<DivisionArray>(divArray);
		return result;
	}

