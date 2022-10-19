#include "JsonEnemyCreator.h"


using namespace Sample;


JsonEnemyCreator::JsonEnemyCreator():
	dictionary()
{
}

EnemyArrayPtr JsonEnemyCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return EnemyArrayPtr();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

EnemyArrayPtr JsonEnemyCreator::Create(nlohmann::json& os)
{
	std::ifstream ifs("Text/EnemyStatus.json");
	nlohmann::json stateOs = nlohmann::json::parse(ifs);

	EnemyArrayPtr	Enemys;

	for (auto& enemy : os)
	{
		CVector3 pos;
		std::string type;
		enemy["PosX"].get_to(pos.x);
		enemy["PosY"].get_to(pos.y);
		enemy["PosZ"].get_to(pos.z);
		enemy["Type"].get_to(type);



		auto& dicValue = dictionary.GetDictionary(type);
		

		EnemyPtr ene;
		ene = std::make_shared<CEnemy>();
		ene->Load(pos, dicValue.actionCreator, dicValue.stateCreator,dicValue.parameterCreator,dicValue.aiCreator);
		Enemys->push_back(ene);
	}
	return Enemys;
}

class EnemyTest
{
public:
};


class EnemyBuildParameter
{
};

class EnemyBuilder
{
public:
	EnemyTest* Create(const EnemyBuildParameter& param);
};

class ZombiEnemyBuilder : public EnemyBuilder
{
public:
	EnemyTest* Create(const EnemyBuildParameter& param);
};

class EnemyBuilderDictyonary
{
	std::map<EnemyBuilder> map;
};
class JsonEnemyLoader
{
public:
	std::vector< EnemyBuildParameter> load();
};

class JsonEnemyStatusLoader
{
public:
	EnemyBuilderDictyonary load();
};
gameSceneLoad()
{
	std::vector< EnemyBuildParameter> parameter = JsonEnemyLoader.load();
	EnemyBuilderDictyonary dic = JsonEnemyStatusLoader.Load();
}

divisonCreate()
{
	enemys.push_back(dic[parameter[i].type].Create(parameter[i]));
}