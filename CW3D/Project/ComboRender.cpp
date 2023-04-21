#include "ComboRender.h"
#include "ResourceManager.h"

ActionGame::CComboRender::CComboRender()
	: comboCount_(0)
	, font_(nullptr)
	, position_(0,0)

{
}

ActionGame::CComboRender::~CComboRender()
{
}

bool ActionGame::CComboRender::Load()
{
	font_ = ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "ComboFont");
	if (font_ == nullptr)
	{
		return false;
	}
	return true;
}

void ActionGame::CComboRender::Initialize()
{
	position_ = Vector2(250, 300);
	font_->SetSize(100);
	font_->SetBold(60);
}

void ActionGame::CComboRender::Render()
{
	if (comboCount_ <= 0)
	{
		return;
	}
	


	const auto str = std::to_string(comboCount_);
	CRectangle rect;
	font_->CalculateStringRect(0,0,str.c_str(),rect);
	font_->RenderFormatString(position_.x - rect.GetWidth(), position_.y, str.c_str());
	font_->RenderFormatString(position_.x , position_.y, "Combo");

}

void ActionGame::CComboRender::Release()
{
	font_.reset();
}

void ActionGame::CComboRender::SetComboCount(uint32_t count) noexcept
{
	comboCount_ = count;

	if (comboCount_ > COMBO_MAX)
	{
		comboCount_ = COMBO_MAX;
	}
}
