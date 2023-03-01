#include "ClearTermBuilderDictionary.h"
#include "ClearTermEnemysAllDeadBuilder.h"
#include "ClearTermEnduranceTimeBuilder.h"
#include "ClearTermBossDeadBuilder.h"


ClearTerm::CBuilderDictionary::CBuilderDictionary()
{
	dictionary_["AllDead"] = std::make_shared<CEnemysAllDeadBuilder>();
	dictionary_["EnduranceTime"] = std::make_shared<CEnduranceTimeBuilder>();
	dictionary_["FixedDead"] = std::make_shared<CEnemysAllDeadBuilder>();
	dictionary_["BossDead"] = std::make_shared<CBossDeadBuilder>();
}

ClearTerm::CBuilderDictionary::~CBuilderDictionary()
{
}
