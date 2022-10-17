#include "ClearTermEnemysAllDead.h"


using namespace Sample;

ClearTermEnemysAllDead::ClearTermEnemysAllDead()
{
}

bool ClearTermEnemysAllDead::IsClear(const ClearTermProviderPtr& provider)
{
    if (provider->GetEnemyCount() <= 0)
    {
        return true;
    }
    return false;
}