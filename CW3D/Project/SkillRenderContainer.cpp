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
	auto& player = ServiceLocator< CPlayer >::GetService();
	auto& skillController = player->GetSkillController();
	for (size_t i = 0; i < skillController->GetCount(); i++)
	{
		auto& skillPtr = skillController->GetSkill(i);

		SkillRenderPtr render;
		if (std::dynamic_pointer_cast<AdditionalSkill>(skillPtr) != nullptr)
		{
			//追加攻撃スキルならロード
			auto addRender = std::make_shared<CAdditionalSkillRender>();
			CSkillPresenter::Present(player, addRender, i);
			render = addRender;
		}
		else
		{
			render = std::make_shared<CSkillRender>();
		}
		CSkillPresenter::Present(player, render, i);

		render->Load(skillPtr->GetTexName());
		skillRenderArray_.push_back(render);

		//必殺技ならロード
		if (std::dynamic_pointer_cast<UltimateSkill>(skillPtr) != nullptr)
		{
			auto gauge = std::make_shared<CSkillUltGaugeRender>();
			gauge->Load();
			CSkillUltGaugePresenter::Present(player, gauge, i);
			ultGaugeRenderArray_.push_back(gauge);
		}
	}

	return true;
}

void ActionGame::CSkillRenderContainer::Initialize(std::function<Vector2(const std::string&)> fn)
{
	auto& player = ServiceLocator< CPlayer >::GetService();
	auto& skillController = player->GetSkillController();
	size_t ultIndex = 0;
	for (size_t i = 0; i < skillController->GetCount(); i++)
	{
		auto& skillPtr = skillController->GetSkill(i);
		skillRenderArray_[i]->Initialize(fn(skillPtr->GetButton()));

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
