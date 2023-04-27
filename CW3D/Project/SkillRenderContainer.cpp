#include "SkillRenderContainer.h"

ActionGame::CSkillRenderContainer::CSkillRenderContainer()
{
}

ActionGame::CSkillRenderContainer::~CSkillRenderContainer()
{
	Release();
}

bool ActionGame::CSkillRenderContainer::Load()
{
	auto& player = CServiceLocator< CPlayer >::GetService();
	auto& skillController = player->GetSkillController();
	
	for (size_t i = 0; i < skillController->GetCount(); i++)
	{
		auto& skill = skillController->GetSkill(i);

		SkillRenderPtr render;
		
		//追加入力攻撃スキルならロード
		if (std::dynamic_pointer_cast<CAdditionalSkill>(skill) != nullptr)
		{
			auto addSkill = std::make_shared<CAdditionalSkillRender>();
			CSkillPresenter::Present(player, addSkill, i);
			render = addSkill;
		}
		else
		{
			render = std::make_shared<CSkillRender>();
		}

		CSkillPresenter::Present(player, render, i);

		render->Load(skill->GetTexName());
		skillRenderArray_.push_back(render);

		//必殺技ならロード
		if (std::dynamic_pointer_cast<UltimateSkill>(skill) != nullptr)
		{
			auto ultSkill = std::make_shared<CSkillUltGaugeRender>();
			ultSkill->Load();
			CSkillUltGaugePresenter::Present(player, ultSkill, i);
			ultGaugeRenderArray_.push_back(ultSkill);
		}
	}

	return true;
}

void ActionGame::CSkillRenderContainer::Initialize(PositionFunc func)
{
	auto& player = CServiceLocator< CPlayer >::GetService();
	if (!player) return;
	auto& skillController = player->GetSkillController();
	size_t ultIndex = 0;
	for (size_t i = 0; i < skillController->GetCount(); i++)
	{
		//登録されているボタンの座標で初期化
		auto& skillPtr = skillController->GetSkill(i);
		skillRenderArray_[i]->Initialize(func(skillPtr->GetButton()));

		//必殺技スキルなら必殺技用のフレームを初期化
		if (std::dynamic_pointer_cast<UltimateSkill>(skillPtr) != nullptr)
		{
			ultGaugeRenderArray_[ultIndex++]->Initialize(skillRenderArray_[i]->GetPosition());
		}
	}
}

void ActionGame::CSkillRenderContainer::Render()
{
	for (int i = 0; i < skillRenderArray_.size(); i++)
	{
		skillRenderArray_[i]->Render();
	}
	for (int i = 0; i < ultGaugeRenderArray_.size(); i++)
	{
		ultGaugeRenderArray_[i]->Render();
	}

}

void ActionGame::CSkillRenderContainer::Release()
{
	for (auto skill : skillRenderArray_)
	{
		skill.reset();
	}
	skillRenderArray_.clear();
	for (auto skill : ultGaugeRenderArray_)
	{
		skill.reset();
	}
	ultGaugeRenderArray_.clear();
}
