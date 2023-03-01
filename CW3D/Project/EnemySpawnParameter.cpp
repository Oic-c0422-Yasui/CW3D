#include "EnemySpawnParameter.h"

Spawner::EnemySpawnParameter::EnemySpawnParameter(const ActionGame::EnemyBuildParameterArrayPtr& param)
	: param_(param)
{
}

void Spawner::EnemySpawnParameter::Next()
{
	CurrentParameterNum_++;
	if (param_->size() <= CurrentParameterNum_)
	{
		CurrentParameterNum_ = 0;
	}
}

void Spawner::EnemySpawnParameter::Reset()
{
	param_.reset();
}

const ActionGame::EnemyBuildParameterPtr& Spawner::EnemySpawnParameter::GetParameter() const noexcept
{
	return param_->at(CurrentParameterNum_);
}
