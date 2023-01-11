#include "EnemyBuildParameter.h"

using namespace ActionGame;

ActionGame::EnemyParam::EnemyParam(const std::string& type, const Vector3& pos, bool isBoss)
	: m_Type(type)
	, m_Pos(pos)
	, m_IsBoss(isBoss)

{
}


ActionGame::EnemyBuildParameter::EnemyBuildParameter(const EnemyParam& param, const EnemyStatusPtr& status)
	: m_Param(param)
	, m_Status(status)
{
}


ActionGame::EnemyBuildParameter::~EnemyBuildParameter()
{
}




