#include "EnemyBuildParameter.h"

using namespace Sample;

Sample::EnemyBuildParameter::EnemyBuildParameter(const EnemyParam& param, const EnemyStatusPtr& status)
	: m_Param(param)
	, m_Status(status)
{
}


Sample::EnemyBuildParameter::~EnemyBuildParameter()
{
}



Sample::EnemyParam::EnemyParam(const std::string& type, const Vector3& pos)
	: m_Type(type)
	, m_Pos(pos)
{
}

