#pragma once
#include "Player.h"
#include "UltimateGaugeRender.h"

namespace ActionGame
{
	class CUltGaugePresenter
	{
	public:
		static void Present(const PlayerPtr& player, const ActionGame::UltimateGaugeUIRenderPtr& view)
		{
			player->GetUltSubject().Subscribe([view](float gauge) { view->SetGauge(gauge); });
			player->GetMaxUltSubject()->Subscribe([view](float gauge) { view->SetMaxGauge(gauge); });

			view->SetGauge(0);
			view->SetMaxGauge(player->GetMaxUltGauge());
		}

	};
}

