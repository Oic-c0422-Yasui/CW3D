#pragma once
#include "Player.h"
#include "SkillRender.h"
#include "AdditionalSkillRender.h"

namespace ActionGame
{
	class CSkillPresenter
	{
	public:

		//�ʏ�X�L��
		static void Present(const PlayerPtr& player, const SkillRenderPtr& view, int skillID)
		{
			auto& skill = player->GetSkill(skillID);
			skill->GetCTSubject()->Subscribe([view](float ct) { view->SetCT(ct); });
			skill->GetMaxCTSubject()->Subscribe([view](float ct) { view->SetMaxCT(ct); });
			skill->GetCanUseSubject()->Subscribe([view](bool canUse) {view->SetCanUse(canUse); });

			view->SetCT(0.0f);
			view->SetCanUse(player->GetSkillController()->GetSkill(skillID)->CanUseSkill());
			view->SetMaxCT(player->GetSkillController()->GetSkill(skillID)->GetMaxCT());
		}

		//�ǉ��U���X�L��
		static void Present(const PlayerPtr& player, const AdditionalSkillRenderPtr& view, int skillID)
		{
			auto& skill = player->GetCastSkill<CAdditionalSkill>(skillID);
			skill->GetAddCTSubject()->Subscribe([view](float ct) { view->SetAddCT(ct); });
			skill->GetAddMaxCTSubject()->Subscribe([view](float ct) { view->SetAddMaxCT(ct); });

			view->SetAddCT(0.0f);
			view->SetAddMaxCT(skill->GetAddMaxCT());
		}
	};
}