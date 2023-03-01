#pragma once
#include "SpawnerBuilder.h"

namespace Spawner
{
    class NormalSpawnerBuilder : public SpawnerBuilder
    {
    private:
        float cycleTime_;
    public:
        NormalSpawnerBuilder();

        EnemySpawnerPtr Create() override;
        EnemySpawnerPtr Create(nlohmann::json& os) override;
    };

}


