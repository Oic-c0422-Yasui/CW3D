#pragma once
#include "IClearTerm.h"

namespace Sample
{
	class ClearTermEnemysAllDead : public IClearTerm
	{
	public:
		bool IsClear() override;
		ClearTermEnemysAllDead();
		~ClearTermEnemysAllDead() override = default;
	};
}



