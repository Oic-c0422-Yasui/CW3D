#include "SpawnerBuilderDictionary.h"
#include "NormalSpawnerBuilder.h"

Spawner::SpawnerBuilderDictionary::SpawnerBuilderDictionary()
{
	dictionary["Normal"] = std::make_shared<Spawner::NormalSpawnerBuilder>();
}

Spawner::SpawnerBuilderDictionary::~SpawnerBuilderDictionary()
{
	dictionary.clear();
}
