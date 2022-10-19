#include "EnemyBuildParameter.h"

Sample::EnemyBuildParameter::EnemyBuildParameter(int hp, float ultGauge, int atk, std::string meshName)
	: m_HP(hp)
	, m_UltGauge(ultGauge)
	, m_Attack(atk)
	, m_MeshName(meshName)
{
}

Sample::EnemyBuildParameter::~EnemyBuildParameter()
{
}
