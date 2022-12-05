#include "EnemyBuilderDictionary.h"
#include "ZombieBuilder.h"

ActionGame::EnemyBuilderDictionary::EnemyBuilderDictionary()
{
	map["Zombie"] = std::make_shared<ZombieBuilder>();
	map["Zombie2"] = std::make_shared<ZombieBuilder>();
}

ActionGame::EnemyBuilderDictionary::~EnemyBuilderDictionary()
{
}
