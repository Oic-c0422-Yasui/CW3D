#include "UltimateGaugeRender.h"

ActionGame::CUltimateGaugeRender::CUltimateGaugeRender()
	: gauge_(0.2f)
	, maxGauge_(1.0f)
	, offset_(0, 0)
	, size_(1, 1)
	, position_(634, 1052)
{
}

ActionGame::CUltimateGaugeRender::~CUltimateGaugeRender()
{
	Release();
}

bool ActionGame::CUltimateGaugeRender::Load()
{

	gaugeFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltGauge");
	if (gaugeFrame_ == nullptr)
	{
		return false;
	}
	font_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "SkillFont");
	if (gaugeFrame_ == nullptr)
	{
		return false;
	}

	//•¶ŽšÀ•W
	CRectangle fontrect;
	font_->CalculateStringRect(0, 0, "000/000", fontrect);
	strPosition_ = Vector2(position_.x - (fontrect.GetWidth() * 0.5f), position_.y - gaugeFrame_->GetHeight() * 0.5f - (fontrect.GetHeight() * 0.5f));

	return true;
}

void ActionGame::CUltimateGaugeRender::Render()
{
	float percent = gauge_ / maxGauge_;

	CRectangle rect(0, gaugeFrame_->GetHeight() * (1.0 - percent), gaugeFrame_->GetWidth(), gaugeFrame_->GetHeight());
	gaugeFrame_->Render(position_.x, position_.y, rect, TEXALIGN_BOTTOMCENTER);

	font_->RenderFormatString(strPosition_.x, strPosition_.y, "%03.0f/%03.0f", gauge_, maxGauge_);

}

void ActionGame::CUltimateGaugeRender::Release(void)
{
	gaugeFrame_.reset();
	font_.reset();
}


