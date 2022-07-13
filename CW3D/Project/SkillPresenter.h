#pragma once
#include "Player.h"
#include "SkillRender.h"
#include "AdditionalSkillRender.h"

namespace Sample
{
	class CSkillPresenter
	{
	public:

		//通常スキル
		static void Present(PlayerPtr& player, const SkillRenderPtr& view, int skillID)
		{
			auto& skill = player->GetSkill(skillID);
			skill->GetCTSubject()->Subscribe([view](float ct) { view->SetCT(ct); });
			skill->GetMaxCTSubject()->Subscribe([view](float ct) { view->SetMaxCT(ct); });
			skill->GetCanUseSubject()->Subscribe([view](bool canUse) {view->SetCanUseFlg(canUse); });

			view->SetCT(0.0f);
			view->SetCanUseFlg(player->GetSkillController()->GetSkill(skillID)->IsCanUse());
			view->SetMaxCT(player->GetSkillController()->GetSkill(skillID)->GetMaxCT());
		}

		//追加攻撃スキル
		static void Present(PlayerPtr& player, const AdditionalSkillRenderPtr& view, int skillID)
		{
			auto& skill = player->GetSkillT<CAdditionalSkill>(skillID);
			skill->GetAddCTSubject()->Subscribe([view](float ct) { view->SetAddCT(ct); });
			skill->GetAddMaxCTSubject()->Subscribe([view](float ct) { view->SetAddMaxCT(ct); });

			view->SetAddCT(0.0f);
			view->SetAddMaxCT(skill->GetAddMaxCT());
		}
	};
}