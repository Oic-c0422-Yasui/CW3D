#include "ClearTermEnemysAllDead.h"


Sample::ClearTermEnemysAllDead::ClearTermEnemysAllDead()
{
}

bool Sample::ClearTermEnemysAllDead::IsClear(const Sample::ClearTermProviderPtr& provider)
{
    for (auto enemy : *m_Enemys)
    {
        if (enemy->IsShow())
        {
            return false;
        }
    }
    return true;
}