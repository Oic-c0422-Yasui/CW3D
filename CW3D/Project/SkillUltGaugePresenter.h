#pragma once
#include "Player.h"
#include "SkillUltGaugeRender.h"

namespace Sample
{
	class CSkillUltGaugePresenter
	{
	public:

		static void Present(PlayerPtr& player, const SkillUltGaugeRenderPtr& view, int skillID)
		{
			player->GetUltSubject().Subscribe([view](float gauge) { view->SetGauge(gauge); });
			auto& skill = player->GetCastSkill <CUltimateSkill>(skillID);
			skill->GetSkillUltSubject(skillID)->Subscribe([view](float gauge) { view->SetMaxGauge(gauge); });

			view->SetGauge(0);
			view->SetMaxGauge(skill->GetUltGauge());
		}

	};
}