#include "JsonEnemyStatusLoader.h"

using namespace Sample;

JsonEnemyStatusLoader::JsonEnemyStatusLoader()
{
}

EnemyStatusDictionary JsonEnemyStatusLoader::Load(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return EnemyStatusDictionary();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Load(os);
}

EnemyStatusDictionary JsonEnemyStatusLoader::Load(nlohmann::json& os)
{
	auto& Status = os["Status"];
	EnemyStatusDictionary dictionary;
	
	for (auto& state : Status)
	{
		
		std::string typeName;
		int hp;
		float ultGauge;
		int atk;
		std::string meshName;
		Vector3 colliderSize;
		float colliderHeight;

		state["Type"].get_to(typeName);
		state["HP"].get_to(hp);
		state["UltGauge"].get_to(ultGauge);
		state["ATK"].get_to(atk);
		state["Mesh"].get_to(meshName);
		auto& collider = state["Collider"];
		{
			collider["SizeX"].get_to(colliderSize.x);
			collider["SizeY"].get_to(colliderSize.y);
			collider["SizeZ"].get_to(colliderSize.z);
			collider["Height"].get_to(colliderHeight);
		}
		EnemyStatusPtr enemyStateus = 
			std::make_shared<EnemyStatus>(EnemyStatus(hp,ultGauge,atk,meshName,colliderSize,colliderHeight));
		dictionary.Add(typeName,enemyStateus);
	}
	

	return dictionary;
}
