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
	usedSKillTexture_->Render(position_.x, position_.y, MOF_ARGB(255, 128, 128, 128), TEXALIGN_BOTTOMCENTER);
	CRectangle rect(0, usedSKillTexture_->GetHeight() * percent, usedSKillTexture_->GetWidth(), usedSKillTexture_->GetHeight());
	usedSKillTexture_->Render(position_.x, position_.y, rect, TEXALIGN_BOTTOMCENTER);


	if (addCT_ > 0.0f)
	{
		CRectangle rect(0, usedSKillTexture_->GetHeight() * (1.0f - addPercent), usedSKillTexture_->GetWidth(), usedSKillTexture_->GetHeight());
		sKillTexture_->Render(position_.x, position_.y, rect, TEXALIGN_BOTTOMCENTER);
	}
	if (canUse_)
	{
		sKillTexture_->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);
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
	sKillTexture_.reset();
	font_.reset();
}
