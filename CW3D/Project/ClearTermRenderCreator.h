#pragma once
#include "IClearTerm.h"
#include "ClearTermPresenter.h"

namespace Sample
{
	class ClearTermRenderCreator
	{
	public:

		static ClearTermRenderPtr Create(EnemyManager& manager,CTimer& timer,ClearTermArray& clearTermArray)
		{
			std::vector<ClearTermRenderPtr> tmpRenderers;

			for (auto& clearTerm : clearTermArray)
			{
				if (clearTerm->GetType() == "AllDead")
				{
					ClearTermEnemyAllDeadRenderPtr renderer = std::make_shared<ClearTermEnemyAllDeadRender>();
					ClearTermPresenter::Present(manager, renderer);
					tmpRenderers.push_back(renderer);
				}
				if (clearTerm->GetType() == "EnduranceTime")
				{
					ClearTermEnduranceTimeRenderPtr renderer = std::make_shared<ClearTermEnduranceTimeRender>();
					ClearTermPresenter::Present(timer, renderer);
					tmpRenderers.push_back(renderer);
				}
			}


			return ClearTermRenderPtr();
		}
	};
}


