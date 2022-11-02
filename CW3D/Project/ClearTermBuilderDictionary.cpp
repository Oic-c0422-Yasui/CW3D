#include "ClearTermBuilderDictionary.h"
#include "ClearTermEnemysAllDeadBuilder.h"



Sample::ClearTermBuilderDictionary::ClearTermBuilderDictionary()
{
	dictionary["AllDead"] = std::make_shared<ClearTermEnemysAllDeadBuilder>();
	dictionary["EnduranceTime"] = std::make_shared<ClearTermEnemysAllDeadBuilder>();
	dictionary["FixedDead"] = std::make_shared<ClearTermEnemysAllDeadBuilder>();
}

Sample::ClearTermBuilderDictionary::~ClearTermBuilderDictionary()
{
}
