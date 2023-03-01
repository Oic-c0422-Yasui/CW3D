#pragma once
#include "IClearTerm.h"
#include "ClearTermPresenter.h"

namespace ClearTerm
{
	class ClearTermRenderCreator
	{
	public:

		static ClearTermTextPtr Create(ActionGame::EnemyManager& manager, ActionGame::CTimer& timer,ClearTermArray& clearTermArray)
		{
			std::stringstream sstream;

			for (auto& clearTerm : clearTermArray)
			{
				sstream << clearTerm->GetType();
			}

			std::string termType = sstream.str();

			if (termType == "AllDead")
			{
				EnemyAllDeadTextPtr allDead = std::make_shared<CEnemyAllDeadText>();
				CPresenter::Present(manager, allDead);
				return allDead;
			}
			else if (termType == "EnduranceTime")
			{
				EnduranceTimeTextPtr renderer = std::make_shared<CEnduranceTimeText>();
				CPresenter::Present(timer, renderer);
				return renderer;
			}
			else if (termType == "AllDead_EnduranceTime")
			{
				AllDeadAndEnduranceTextPtr renderer = std::make_shared<CAllDeadAndEnduranceText>();
				CPresenter::Present(manager,timer, renderer);
				return renderer;
			}

			return ClearTermTextPtr();
		}
	};
}


