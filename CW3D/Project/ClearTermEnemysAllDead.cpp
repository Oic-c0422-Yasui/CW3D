#include "ClearTermEnemysAllDead.h"


Sample::ClearTermEnemysAllDead::ClearTermEnemysAllDead()
{
}

bool Sample::ClearTermEnemysAllDead::IsClear(const Sample::ClearTermProviderPtr& provider)
{
    if (provider->GetEnemyCount() <= 0)
    {
        auto count = provider->GetEnemyCount();
        return true;
    }
    return false;
}