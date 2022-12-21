#include "EnemyBuildParameter.h"

using namespace ActionGame;

ActionGame::EnemyBuildParameter::EnemyBuildParameter(const EnemyParam& param, const EnemyStatusPtr& status)
	: m_Param(param)
	, m_Status(status)
{
}


ActionGame::EnemyBuildParameter::~EnemyBuildParameter()
{
}



ActionGame::EnemyParam::EnemyParam(const std::string& type, const Vector3& pos)
	: m_Type(type)
	, m_Pos(pos)

{
}

