#include "EnemyBuilderDictionary.h"
#include "ZombieBuilder.h"

Sample::EnemyBuilderDictionary::EnemyBuilderDictionary()
{
	map["Zombie"] = std::make_shared<ZombieBuilder>();
}

Sample::EnemyBuilderDictionary::~EnemyBuilderDictionary()
{
}
