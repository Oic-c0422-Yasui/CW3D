#include "ClearTermEnemysAllDead.h"


Sample::ClearTermEnemysAllDead::ClearTermEnemysAllDead()
{
}

bool Sample::ClearTermEnemysAllDead::IsClear(const Sample::ClearTermProviderPtr& provider)
{
    for (auto enemy : *provider->GetEnemys())
    {
        if (enemy->IsShow())
        {
            return false;
        }
    }
    return true;
}