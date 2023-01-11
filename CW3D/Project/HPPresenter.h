#pragma once
#include "Enemy.h"
#include "Player.h"
#include "NormalEnemyHPRender.h"
#include "BossHPRender.h"
#include "PlayerHPRender.h"

namespace ActionGame
{
	class CHPPresenter
	{
	public:

		static void Present(const EnemyPtr& enemy, const ActionGame::NormalEnemyHPRenderPtr& view)
		{
			enemy->GetHPSubject()->Subscribe([view](int hp) { view->SetHP(hp); });
			enemy->GetMaxHPSubject()->Subscribe([view](int hp) { view->SetMaxHP(hp); });
			enemy->GetPositionSubject()->Subscribe([view](Vector3 pos) { view->SetPosition(pos); });
			enemy->GetShowSubject().Subscribe([view](bool show) { view->SetShow(show); });

			view->SetHP(enemy->GetHP());
			view->SetMaxHP(enemy->GetHP());
			view->SetPosition(enemy->GetPosition());
			view->SetShow(enemy->IsShow());
		}
		static void Present(const EnemyPtr& enemy, const ActionGame::BossHPRenderPtr& view)
		{
			enemy->GetHPSubject()->Subscribe([view](int hp) { view->SetHP(hp); });
			enemy->GetMaxHPSubject()->Subscribe([view](int hp) { view->SetMaxHP(hp); });
			enemy->GetShowSubject().Subscribe([view](bool show) { view->SetShow(show); });

			view->SetHP(enemy->GetHP());
			view->SetMaxHP(enemy->GetHP());
			view->SetShow(enemy->IsShow());
		}


		static void Present(const PlayerPtr& player, const ActionGame::PlayerHPRenderPtr& view)
		{
			player->GetHPSubject().Subscribe([view](int hp) { view->SetHP(hp); });
			player->GetMaxHPSubject()->Subscribe([view](int hp) { view->SetMaxHP(hp); });

			view->SetHP(player->GetHP());
			view->SetMaxHP(player->GetHP());
		}

	};
}

