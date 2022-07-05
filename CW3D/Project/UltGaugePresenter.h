#pragma once
#include "Player.h"
#include "UltimateGaugeRender.h"
class CUltGaugePresenter
{
public:

	static void Present(PlayerPtr& player, const Sample::UltimateGaugeUIRenderPtr& view)
	{
		player->GetUltSubject().Subscribe([view](float gauge) { view->SetGauge(gauge); });
		player->GetMaxUltSubject()->Subscribe([view](float gauge) { view->SetMaxGauge(gauge); });

		view->SetGauge(0);
		view->SetMaxGauge(player->GetMaxUltGauge());
	}

};