#pragma once
#include "EnemyBuilder.h"

namespace ActionGame
{
    class ZombieBuilder : public EnemyBuilder
    {
    public:
		ZombieBuilder();

        EnemyPtr Create(const EnemyBuildParameterPtr& param) override;
    };
}


