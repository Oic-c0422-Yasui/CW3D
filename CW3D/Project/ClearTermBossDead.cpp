#include "ClearTermBossDead.h"

ClearTerm::CBossDead::CBossDead()
{
}

bool ClearTerm::CBossDead::IsClear(const ClearTerm::ProviderPtr& provider)
{
	if (provider->GetBossCount() <= 0)
	{
		return true;
	}
	return false;
}
