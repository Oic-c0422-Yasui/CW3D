#include "EnemySpawnParameter.h"

Spawner::EnemySpawnParameter::EnemySpawnParameter(const ActionGame::EnemyBuildParameterArrayPtr& param)
	: param_(param)
{
}

void Spawner::EnemySpawnParameter::Next()
{
	currentParameterNum_++;
	if (param_->size() <= currentParameterNum_)
	{
		currentParameterNum_ = 0;
	}
}

void Spawner::EnemySpawnParameter::Reset()
{
	param_.reset();
}

const ActionGame::EnemyBuildParameterPtr& Spawner::EnemySpawnParameter::GetParameter() const noexcept
{
	return param_->at(currentParameterNum_);
}
