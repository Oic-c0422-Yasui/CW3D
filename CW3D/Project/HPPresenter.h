#pragma once
#include "Enemy.h"
#include "Player.h"
#include "EnemyHPRender.h"

namespace Sample
{
	class CHPPresenter
	{
	public:

		static void Present(CEnemy* enemy, const Sample::EnemyHPRenderPtr& view)
		{
			enemy->GetHPSubject()->Subscribe([view](int hp) { view->SetHP(hp); });
			enemy->GetMaxHPSubject()->Subscribe([view](int hp) { view->SetMaxHP(hp); });
			enemy->GetPositionSubject()->Subscribe([view](Vector3 pos) { view->SetPosition(pos); });
			enemy->GetShowSubject()->Subscribe([view](bool show) { view->SetShow(show); });

			view->SetHP(enemy->GetHP());
			view->SetMaxHP(enemy->GetHP());
			view->SetPosition(enemy->GetPosition());
			view->SetShow(enemy->IsShow());
		}

	};
}

