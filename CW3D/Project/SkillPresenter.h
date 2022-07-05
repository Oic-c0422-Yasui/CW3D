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
		player->GetCanUseSubject(skillID)->Subscribe([view](bool canUse) {view->SetCanUseFlg(canUse); });

		view->SetCT(0);
		view->SetCanUseFlg(true);
		view->SetMaxCT(player->GetSkillController()->GetSkill(skillID)->GetCT());
	}

};