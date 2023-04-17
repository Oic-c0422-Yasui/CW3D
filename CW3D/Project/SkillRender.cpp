#include "SkillRender.h"
#include "ResourceManager.h"

ActionGame::CSkillRender::CSkillRender()
	: CT_(0.0f)
	, maxCT_(0.0f)
	, offset_(0, 0)
	, size_(0, 0)
	, position_(0, 0)
	, canUse_(false)
	, sKillTexture_(nullptr)
	, usedSKillTexture_(nullptr)
	, font_(nullptr)
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
	sKillTexture_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", skillName);
	if (sKillTexture_ == nullptr)
	{
		return false;
	}

	usedSKillTexture_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", skillName + "Mono");
	if (usedSKillTexture_ == nullptr)
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
	
	//�摜�̐^�񒆂ɍ��W�����킹��
	position_.y += sKillTexture_->GetHeight() * 0.5f;
}

void ActionGame::CSkillRender::Render()
{

	float percent = CT_ / maxCT_;
	percent = std::clamp(percent, 0.0f, 1.0f);

	//�X�L�����g�p�\���H
	if (canUse_)
	{
		//�g�p�\�t���[���`��
		sKillTexture_->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);
	}
	else
	{
		//�g�p�s�iCT���j�t���[���`��
		usedSKillTexture_->Render(position_.x, position_.y, MOF_ARGB(255, 128, 128, 128), TEXALIGN_BOTTOMCENTER);
		CRectangle rect(0, usedSKillTexture_->GetHeight() * percent, usedSKillTexture_->GetWidth(), usedSKillTexture_->GetHeight());
		usedSKillTexture_->Render(position_.x, position_.y, rect, TEXALIGN_BOTTOMCENTER);
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
		font_->RenderFormatString(position_.x - (rect.GetWidth() * 0.5f),
			position_.y - usedSKillTexture_->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.0f", ct);
	}
	//�N�[���^�C����1�b�����Ȃ珬���_�܂ŕ`��
	else
	{
		CRectangle rect;
		font_->CalculateStringRect(0, 0, "0.0", rect);
		font_->RenderFormatString(position_.x - (rect.GetWidth() * 0.5f),
			position_.y - usedSKillTexture_->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.1f", ct);
	}
}

void ActionGame::CSkillRender::Release()
{
	sKillTexture_.reset();
	usedSKillTexture_.reset();
	font_.reset();
}
