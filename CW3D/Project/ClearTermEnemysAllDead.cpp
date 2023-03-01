#include "ClearTermEnemysAllDead.h"


ClearTerm::CEnemysAllDead::CEnemysAllDead()
{
}

bool ClearTerm::CEnemysAllDead::IsClear(const ClearTerm::ProviderPtr& provider)
{
    if (provider->GetEnemyCount() <= 0)
    {
        auto count = provider->GetEnemyCount();
        return true;
    }
    return false;
}