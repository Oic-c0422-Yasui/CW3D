#include "ClearTermBossDead.h"

ActionGame::ClearTermBossDead::ClearTermBossDead()
{
}

bool ActionGame::ClearTermBossDead::IsClear(const ClearTermProviderPtr& provider)
{
	
	return provider->GetBossCount() <= 0;
}
