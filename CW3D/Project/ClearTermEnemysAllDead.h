#pragma once
#include "IClearTerm.h"
#include "Enemy.h"

namespace Sample
{
	class ClearTermEnemysAllDead : public IClearTerm
	{
	private:
		EnemyArrayPtr m_Enemys;
	public:
		ClearTermEnemysAllDead();
		bool IsClear(const ClearTermProviderPtr& provider) override;
	};
}



