#pragma once
#include "Player.h"
#include "SkillUltGaugeRender.h"
class CSkillUltGaugePresenter
{
public:

	static void Present(PlayerPtr& player, const Sample::SkillUltGaugeRenderPtr& view,int skillID)
	{
		player->GetUltSubject().Subscribe([view](float gauge) { view->SetGauge(gauge); });
		player->GetSkillUltSubject(skillID)->Subscribe([view](float gauge) { view->SetMaxGauge(gauge); });

		view->SetGauge(0);
		view->SetMaxGauge(player->GetSkillController()->GetSkill(skillID)->GetUltGauge());
	}

};