#include "SpawnerBuilderDictionary.h"
#include "NormalSpawnerBuilder.h"

Spawner::CBuilderDictionary::CBuilderDictionary()
{
	dictionary_["Normal"] = std::make_shared<Spawner::NormalSpawnerBuilder>();
}

Spawner::CBuilderDictionary::~CBuilderDictionary()
{
	dictionary_.clear();
}
