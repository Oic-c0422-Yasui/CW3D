#pragma once
#include "IClearTerm.h"
#include "ClearTermPresenter.h"

namespace Sample
{
	class ClearTermRenderCreator
	{
	public:

		static ClearTermTextPtr Create(EnemyManager& manager,CTimer& timer,ClearTermArray& clearTermArray)
		{
			std::stringstream sstream;

			for (auto& clearTerm : clearTermArray)
			{
				sstream << clearTerm->GetType();
			}

			std::string termType = sstream.str();

			if (termType == "AllDead")
			{
				ClearTermEnemyAllDeadTextPtr allDead = std::make_shared<ClearTermEnemyAllDeadText>();
				ClearTermPresenter::Present(manager, allDead);
				return allDead;
			}
			else if (termType == "EnduranceTime")
			{
				ClearTermEnduranceTimeTextPtr renderer = std::make_shared<ClearTermEnduranceTimeText>();
				ClearTermPresenter::Present(timer, renderer);
				return renderer;
			}
			else if (termType == "AllDead_EnduranceTime")
			{
				ClearTermAllDeadAndEnduranceTextPtr renderer = std::make_shared<ClearTermAllDeadAndEnduranceText>();
				ClearTermPresenter::Present(manager,timer, renderer);
				return renderer;
			}

			return ClearTermTextPtr();
		}
	};
}


