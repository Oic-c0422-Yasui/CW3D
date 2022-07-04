#pragma once
#include "Player.h"
#include "SkillUIRender.h"
class CSkillPresenter
{
public:

	static void Present(PlayerPtr& player, const Sample::SkillUIRenderPtr& view, int skillID)
	{
		player->GetCTSubject(skillID)->Subscribe([view](float ct) { view->SetCT(ct); });
		player->GetMaxCTSubject(skillID)->Subscribe([view](float ct) { view->SetMaxCT(ct); });
		
		view->SetCT(0);
		view->SetMaxCT(player->GetSkillController()->GetSkill(skillID)->GetCT());
	}

};