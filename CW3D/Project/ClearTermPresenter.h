#pragma once
#include "ClearTermProvider.h"
#include "ClearTermEnemyAllDeadText.h"
#include "ClearTermEnduranceTimeText.h"
#include "ClearTermAllDeadAndEnduranceText.h"
#include "IClearTerm.h"
#include "Timer.h"
#include "EnemyManager.h"

namespace ClearTerm
{
	class CPresenter
	{
	public:

		static void Present(ActionGame::CEnemyManager& enemy,const ClearTerm::EnemyAllDeadTextPtr& view)
		{
			enemy.GetEnemyCountSubject().Subscribe([view](size_t count) {view->SetEnemyCount(count); });
		}

		static void Present(ActionGame::CTimer& timer, const ClearTerm::EnduranceTimeTextPtr& view)
		{
			timer.GetTimeSubject().Subscribe([view](float time) {view->SetCurrentTime(time); });
			view->SetFinishTime(timer.GetTargetTime());
		}

		static void Present(ActionGame::CEnemyManager& enemy, ActionGame::CTimer& timer,
			const ClearTerm::AllDeadAndEnduranceTextPtr& view)
		{
			Present(enemy, view->GetAllDeadTerm());
		}	
	};

}