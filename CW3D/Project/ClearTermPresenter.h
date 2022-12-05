#pragma once
#include "ClearTermProvider.h"
#include "ClearTermEnemyAllDeadText.h"
#include "ClearTermEnduranceTimeText.h"
#include "ClearTermAllDeadAndEnduranceText.h"
#include "IClearTerm.h"
#include "Timer.h"
#include "EnemyManager.h"

namespace ActionGame
{
	class ClearTermPresenter
	{
	public:

		static void Present(EnemyManager& enemy,const ClearTermEnemyAllDeadTextPtr& view)
		{
			enemy.GetEnemyCountSubject().Subscribe([view](size_t count) {view->SetEnemyCount(count); });
		}

		static void Present(CTimer& timer, const ClearTermEnduranceTimeTextPtr& view)
		{
			timer.GetTimeSubject().Subscribe([view](float time) {view->SetCurrentTime(time); });
			view->SetFinishTime(timer.GetTargetTime());
		}

		static void Present(EnemyManager& enemy, CTimer& timer, const ClearTermAllDeadAndEnduranceTextPtr& view)
		{
			Present(enemy, view->GetAllDeadTerm());
		}	
	};

}