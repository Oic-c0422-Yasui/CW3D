#pragma once
#include "ClearTermRender.h"
#include "ClearTermProvider.h"
#include "ClearTermEnemyAllDeadRender.h"
#include "IClearTerm.h"
#include "Timer.h"
#include "EnemyManager.h"

namespace Sample
{
	class ClearTermPresenter
	{
	public:

		static void Present(const EnemyManager& enemy, ClearTermPtr& term, ClearTermRenderPtr& view)
		{
			term->GetDescription();
			
		}

	};

}