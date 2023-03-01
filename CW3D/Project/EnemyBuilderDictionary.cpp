#include "EnemyBuilderDictionary.h"
#include "ZombieBuilder.h"
#include "MutantBuilder.h"

ActionGame::EnemyBuilderDictionary::EnemyBuilderDictionary()
{
	map_["Zombie"] = std::make_shared<ZombieBuilder>();
	map_["Zombie2"] = std::make_shared<ZombieBuilder>();
	map_["Mutant"] = std::make_shared<MutantBuilder>();
}

ActionGame::EnemyBuilderDictionary::~EnemyBuilderDictionary()
{
}
