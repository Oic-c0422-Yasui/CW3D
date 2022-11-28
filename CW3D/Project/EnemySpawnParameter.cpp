#include "EnemySpawnParameter.h"

Spawner::EnemySpawnParameter::EnemySpawnParameter(const Sample::EnemyBuildParameterArrayPtr& param)
	: m_Param(param)
{
}

void Spawner::EnemySpawnParameter::Next()
{
	m_CurrentParameterNum++;
	if (m_Param->size() <= m_CurrentParameterNum)
	{
		m_CurrentParameterNum = 0;
	}
}

void Spawner::EnemySpawnParameter::Reset()
{
	m_Param.reset();
}

const Sample::EnemyBuildParameterPtr& Spawner::EnemySpawnParameter::GetParameter() const noexcept
{
	return m_Param->at(m_CurrentParameterNum);
}
