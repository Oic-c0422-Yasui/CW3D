#include "UltimateGaugeRender.h"
#include "ResourceManager.h"
#include "Utilities.h"

ActionGame::CUltimateGaugeRender::CUltimateGaugeRender()
	: gauge_(0.2f)
	, maxGauge_(1.0f)
	, size_(1, 1)
	, position_(1054, 1046)
	, offset_(47, 0)
{
}

ActionGame::CUltimateGaugeRender::~CUltimateGaugeRender()
{
	Release();
}

bool ActionGame::CUltimateGaugeRender::Load()
{

	gaugeBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltGauge");
	if (gaugeBar_ == nullptr)
	{
		return false;
	}
	gaugeFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltGaugeFrame");
	if (gaugeFrame_ == nullptr)
	{
		return false;
	}
	font_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "SkillFont");
	if (font_ == nullptr)
	{
		return false;
	}

	//•¶ŽšÀ•W
	CRectangle fontrect;
	font_->CalculateStringRect(0, 0, "000/000", fontrect);
	strPosition_ = Vector2(position_.x + (fontrect.GetWidth() * 0.5f) + 130, position_.y);

	return true;
}

void ActionGame::CUltimateGaugeRender::Render()
{
	float percent = gauge_ / maxGauge_;
	percent = std::clamp(percent, 0.0f, 1.0f);

	//MyUtil::RenderMousePos(position_);
	gaugeFrame_->Render(position_.x, position_.y);
	CRectangle rect(0, 0, gaugeBar_->GetWidth() * (percent), gaugeBar_->GetHeight());
	gaugeBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect);

	font_->RenderFormatString(strPosition_.x, strPosition_.y, "%03.0f/%03.0f", gauge_, maxGauge_);

}

void ActionGame::CUltimateGaugeRender::Release()
{
	gaugeBar_.reset();
	gaugeFrame_.reset();
	font_.reset();
}


