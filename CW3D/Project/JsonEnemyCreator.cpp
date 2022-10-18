#include "JsonEnemyCreator.h"

using namespace Sample;


JsonEnemyCreator::JsonEnemyCreator():
	dictionary()
{
}

std::vector<EnemyPtr> JsonEnemyCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return std::vector<EnemyPtr>();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

std::vector<EnemyPtr> JsonEnemyCreator::Create(nlohmann::json& os)
{
	std::vector<EnemyPtr>	Enemys;
	for (auto& enemy : os)
	{
		EnemyPtr ene;
		CVector3 pos;
		std::string type;
		enemy["PosX"].get_to(pos.x);
		enemy["PosY"].get_to(pos.y);
		enemy["PosZ"].get_to(pos.z);
		enemy["Type"].get_to(type);
		auto& dicValue = dictionary.GetDictionary(type);
		ene = std::make_shared<CEnemy>(pos, dicValue.actionCreator, dicValue.stateCreator);
		Enemys.push_back(ene);
	}
	return Enemys;
}