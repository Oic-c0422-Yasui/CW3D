#pragma once
#include "EnemyBuilder.h"

namespace Sample
{
    class ZombieBuilder : public EnemyBuilder
    {
    public:
		ZombieBuilder();

        EnemyPtr Create(const EnemyBuildParameter& param) override;
    };
}


