#include "ClearTermEnemysAllDead.h"


ActionGame::ClearTermEnemysAllDead::ClearTermEnemysAllDead()
{
}

bool ActionGame::ClearTermEnemysAllDead::IsClear(const ActionGame::ClearTermProviderPtr& provider)
{
    if (provider->GetEnemyCount() <= 0)
    {
        auto count = provider->GetEnemyCount();
        return true;
    }
    return false;
}