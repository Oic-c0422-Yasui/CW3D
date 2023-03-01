#include "ClearTermEnemysAllDeadBuilder.h"

ClearTerm::CEnemysAllDeadBuilder::CEnemysAllDeadBuilder()
{
}

ClearTerm::ClearTermPtr ClearTerm::CEnemysAllDeadBuilder::Create(nlohmann::json& os)
{
	return Create();
}

ClearTerm::ClearTermPtr ClearTerm::CEnemysAllDeadBuilder::Create()
{

	ClearTermPtr result = std::make_shared<CEnemysAllDead>();
	return result;
	
}
