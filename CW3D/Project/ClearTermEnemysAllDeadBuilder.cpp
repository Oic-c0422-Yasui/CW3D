#include "ClearTermEnemysAllDeadBuilder.h"

ActionGame::ClearTermEnemysAllDeadBuilder::ClearTermEnemysAllDeadBuilder()
{
}

ActionGame::ClearTermPtr ActionGame::ClearTermEnemysAllDeadBuilder::Create(nlohmann::json& os)
{
	return Create();
}

ActionGame::ClearTermPtr ActionGame::ClearTermEnemysAllDeadBuilder::Create()
{

	ClearTermPtr result = std::make_shared<ClearTermEnemysAllDead>();
	return result;
	
}
