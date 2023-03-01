#include "JsonSpawnerCreator.h"
#include "SpawnerBuilderDictionary.h"

Spawner::JsonSpawnerCreator::JsonSpawnerCreator()
{
}

Spawner::EnemySpawnerPtr Spawner::JsonSpawnerCreator::Create(const std::string& name)
{
	std::ifstream ifs(name);
	if (ifs.fail())
	{
		return EnemySpawnerPtr();
	}
	nlohmann::json os = nlohmann::json::parse(ifs);
	return Create(os);
}

Spawner::EnemySpawnerPtr Spawner::JsonSpawnerCreator::Create(nlohmann::json& os)
{
	std::string typeName;
	os["Type"].get_to(typeName);

	Spawner::CBuilderDictionary dictionary;

	//辞書からビルダーを取得
	auto builder = dictionary.Get(typeName);

	//ビルダーからスポナーを作成
	auto spawner = builder->Create(os);

	return spawner;
}
