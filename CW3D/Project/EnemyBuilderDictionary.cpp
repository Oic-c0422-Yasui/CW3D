#include "EnemyBuilderDictionary.h"
#include "ZombieBuilder.h"
#include "MutantBuilder.h"

ActionGame::EnemyBuilderDictionary::EnemyBuilderDictionary()
{
	map["Zombie"] = std::make_shared<ZombieBuilder>();
	map["Zombie2"] = std::make_shared<ZombieBuilder>();
	map["Mutant"] = std::make_shared<MutantBuilder>();
}

ActionGame::EnemyBuilderDictionary::~EnemyBuilderDictionary()
{
}
