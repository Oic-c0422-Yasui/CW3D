#pragma once
#include "Player.h"
#include "SkillRender.h"
#include "AdditionalSkillRender.h"
class CSkillPresenter
{
public:

	//通常スキル
	static void Present(PlayerPtr& player, const Sample::SkillRenderPtr& view, int skillID)
	{
		player->GetCTSubject(skillID)->Subscribe([view](float ct) { view->SetCT(ct); });
		player->GetMaxCTSubject(skillID)->Subscribe([view](float ct) { view->SetMaxCT(ct); });
		player->GetCanUseSubject(skillID)->Subscribe([view](bool canUse) {view->SetCanUseFlg(canUse); });

		view->SetCT(0);
		view->SetCanUseFlg(player->GetSkillController()->GetSkill(skillID)->GetCanUseFlg());
		view->SetMaxCT(player->GetSkillController()->GetSkill(skillID)->GetCT());
	}

	//追加攻撃スキル
	static void Present(PlayerPtr& player, const Sample::AdditionalSkillRenderPtr& view, int skillID)
	{
		player->GetCTSubject(skillID)->Subscribe([view](float ct) { view->SetAddCT(ct); });
		player->GetMaxCTSubject(skillID)->Subscribe([view](float ct) { view->SetAddMaxCT(ct); });
	}
};