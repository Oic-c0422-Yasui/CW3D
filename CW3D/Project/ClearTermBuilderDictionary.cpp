#include "ClearTermBuilderDictionary.h"
#include "ClearTermEnemysAllDeadBuilder.h"
#include "ClearTermEnduranceTimeBuilder.h"



Sample::ClearTermBuilderDictionary::ClearTermBuilderDictionary()
{
	dictionary["AllDead"] = std::make_shared<ClearTermEnemysAllDeadBuilder>();
	dictionary["EnduranceTime"] = std::make_shared<ClearTermEnduranceTimeBuilder>();
	dictionary["FixedDead"] = std::make_shared<ClearTermEnemysAllDeadBuilder>();
}

Sample::ClearTermBuilderDictionary::~ClearTermBuilderDictionary()
{
}
