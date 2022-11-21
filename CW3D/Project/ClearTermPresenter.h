#pragma once
#include "ClearTermProvider.h"
#include "ClearTermEnemyAllDeadRender.h"
#include "ClearTermEnduranceTimeRender.h"
#include "IClearTerm.h"
#include "Timer.h"
#include "EnemyManager.h"

namespace Sample
{
	class ClearTermPresenter
	{
	public:

		static void Present(EnemyManager& enemy,ClearTermEnemyAllDeadRenderPtr& view)
		{
			enemy.GetEnemyCountSubject().Subscribe([view](size_t count) {view->SetEnemyCount(count); });
			enemy.GetEnemyMaxCountSubject().Subscribe([view](size_t count) {view->SetEnemyMaxCount(count); });
		}

		static void Present(CTimer& timer,ClearTermEnduranceTimeRenderPtr& view)
		{
			timer.GetTimeSubject().Subscribe([view](float time) {view->SetCurrentTime(time); });
			view->SetFinishTime(timer.GetTargetTime());
		}

	};

}