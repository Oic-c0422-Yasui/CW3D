#include "SkillRender.h"
#include "ResourceManager.h"

ActionGame::CSkillRender::CSkillRender()
	: CT_(0.0f)
	, maxCT_(0.0f)
	, offset_(0, 0)
	, size_(0, 0)
	, position_(0, 0)
	, canUse_(false)
{
	offset_ = Vector2(0, 0);
	size_ = Vector2(1, 1);
}

ActionGame::CSkillRender::~CSkillRender()
{
	Release();
}

bool ActionGame::CSkillRender::Load(const std::string& skillName)
{
	sKillFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", skillName);
	if (sKillFrame_ == nullptr)
	{
		return false;
	}

	usedSKillFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", skillName + "Mono");
	if (usedSKillFrame_ == nullptr)
	{
		return false;
	}

	font_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "CTFont");
	if (font_ == nullptr)
	{
		return false;
	}



	return true;
}


void ActionGame::CSkillRender::Initialize(const Vector2& pos)
{
	position_ = pos;
	
	//画像の真ん中に座標を合わせる
	position_.y += sKillFrame_->GetHeight() * 0.5f;
}

void ActionGame::CSkillRender::Render()
{

	float percent = CT_ / maxCT_;
	percent = std::clamp(percent, 0.0f, 1.0f);
	usedSKillFrame_->Render(position_.x, position_.y, MOF_ARGB(255, 128, 128, 128), TEXALIGN_BOTTOMCENTER);
	CRectangle rect(0, usedSKillFrame_->GetHeight() * percent, usedSKillFrame_->GetWidth(), usedSKillFrame_->GetHeight());
	usedSKillFrame_->Render(position_.x, position_.y, rect, TEXALIGN_BOTTOMCENTER);

	if (canUse_)
	{
		sKillFrame_->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);
	}


	RenderCT(CT_);
}

void ActionGame::CSkillRender::RenderCT(float ct)
{
	if (ct <= 0.0f)
	{
		return;
	}

	if (ct > 1.0f)
	{
		CRectangle rect;
		font_->CalculateStringRect(0, 0, "0", rect);
		font_->RenderFormatString(position_.x - (rect.GetWidth() * 0.5f), position_.y - usedSKillFrame_->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.0f", ct);
	}
	//クールタイムが1秒未満なら小数点まで描画
	else
	{
		CRectangle rect;
		font_->CalculateStringRect(0, 0, "0.0", rect);
		font_->RenderFormatString(position_.x - (rect.GetWidth() * 0.5f), position_.y - usedSKillFrame_->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.1f", ct);
	}
}

void ActionGame::CSkillRender::Release()
{
}
