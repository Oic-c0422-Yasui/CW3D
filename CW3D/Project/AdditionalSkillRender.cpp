#include "AdditionalSkillRender.h"

ActionGame::CAdditionalSkillRender::CAdditionalSkillRender()
	: CSkillRender()
	, addCT_(0.0f)
	, addMaxCT_(0.0f)
{
}

ActionGame::CAdditionalSkillRender::~CAdditionalSkillRender()
{
	Release();
}

bool ActionGame::CAdditionalSkillRender::Load(const std::string& key)
{
	if (CSkillRender::Load(key) == false)
	{
		return false;
	}
	return true;
}

void ActionGame::CAdditionalSkillRender::Initialize(const Vector2& pos)
{
	CSkillRender::Initialize(pos);
}

void ActionGame::CAdditionalSkillRender::Render()
{

	float percent = CT_ / maxCT_;
	percent = min(percent, 1.0f);
	float addPercent = addCT_ / addMaxCT_;
	addPercent = min(addPercent, 1.0f);
	usedSKillFrame_->Render(position_.x, position_.y, MOF_ARGB(255, 128, 128, 128), TEXALIGN_BOTTOMCENTER);
	CRectangle rect(0, usedSKillFrame_->GetHeight() * percent, usedSKillFrame_->GetWidth(), usedSKillFrame_->GetHeight());
	usedSKillFrame_->Render(position_.x, position_.y, rect, TEXALIGN_BOTTOMCENTER);


	if (addCT_ > 0.0f)
	{
		CRectangle rect(0, usedSKillFrame_->GetHeight() * (1.0f - addPercent), usedSKillFrame_->GetWidth(), usedSKillFrame_->GetHeight());
		sKillFrame_->Render(position_.x, position_.y, rect, TEXALIGN_BOTTOMCENTER);
	}
	if (canUse_)
	{
		sKillFrame_->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);
	}

	if (addCT_ > 0.0f)
	{
		RenderCT(addCT_);
	}
	else
	{
		RenderCT(CT_);
	}

}

void ActionGame::CAdditionalSkillRender::Release()
{
	sKillFrame_.reset();
	font_.reset();
}
