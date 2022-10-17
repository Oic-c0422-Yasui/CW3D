#pragma once
#include "IClearTerm.h"

namespace Sample
{
	class ClearTermEnemysAllDead : public IClearTerm
	{
	public:
		ClearTermEnemysAllDead();
		~ClearTermEnemysAllDead() override = default;
		bool IsClear(const ClearTermProviderPtr& provider) override;
	};
}



