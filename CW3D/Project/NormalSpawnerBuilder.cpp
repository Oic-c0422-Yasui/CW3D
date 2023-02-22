#include "NormalSpawnerBuilder.h"
#include "SpawnCycleFixedRange.h"

using namespace Spawner;

Spawner::NormalSpawnerBuilder::NormalSpawnerBuilder()
    : m_CycleTime(0.0f)
{
}


EnemySpawnerPtr Spawner::NormalSpawnerBuilder::Create(nlohmann::json& os)
{
    os["Time"].get_to(m_CycleTime);

    return Create();
}

EnemySpawnerPtr Spawner::NormalSpawnerBuilder::Create()
{
    auto spawner = std::make_shared<CEnemySpawner>(
        Spawner::SpawnConditionArray{ },
        std::make_shared<Spawner::SpawnCycleFixedRange>(m_CycleTime, CHARA_TYPE::ENEMY)
        );
    return spawner;
}
