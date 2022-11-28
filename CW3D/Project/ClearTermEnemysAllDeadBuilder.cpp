#include "ClearTermEnemysAllDeadBuilder.h"

Sample::ClearTermEnemysAllDeadBuilder::ClearTermEnemysAllDeadBuilder()
{
}

Sample::ClearTermPtr Sample::ClearTermEnemysAllDeadBuilder::Create(nlohmann::json& os)
{
	return Create();
}

Sample::ClearTermPtr Sample::ClearTermEnemysAllDeadBuilder::Create()
{

	ClearTermPtr result = std::make_shared<ClearTermEnemysAllDead>();
	return result;
	
}
