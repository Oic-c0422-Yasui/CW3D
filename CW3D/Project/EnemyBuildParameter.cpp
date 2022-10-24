#include "EnemyBuildParameter.h"

Sample::EnemyBuildParameter::EnemyBuildParameter(const std::string& typeName, const Vector3& pos)
	: m_Type(typeName)
	, m_Pos(pos)
{
}

Sample::EnemyBuildParameter::~EnemyBuildParameter()
{
}
