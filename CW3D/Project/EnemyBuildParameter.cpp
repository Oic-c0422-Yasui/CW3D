#include "EnemyBuildParameter.h"

using namespace ActionGame;

ActionGame::EnemyParam::EnemyParam(const std::string& type, const Vector3& pos, bool isBoss)
	: type_(type)
	, position_(pos)
	, isBoss_(isBoss)

{
}


ActionGame::EnemyBuildParameter::EnemyBuildParameter(const EnemyParam& param, const EnemyStatusPtr& status)
	: param_(param)
	, status_(status)
{
}


ActionGame::EnemyBuildParameter::~EnemyBuildParameter()
{
}




