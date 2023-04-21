#include "ComboRender.h"
#include "ResourceManager.h"

ActionGame::CComboRender::CComboRender()
	: comboCount_(0)
	, prevComboCount_(0)
	, font_(nullptr)
	, position_(0, 0)
	, quake_()
	, fade_()
	, isFade_(false)
	, isShow_(false)

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
	quake_.Initialize(15.0f, 40.0f, 0.2f);
	fade_.Initialize(255, 1.2f, 0);
	prevComboCount_ = 0;
	isFade_ = false;
	isShow_ = false;
}

void ActionGame::CComboRender::Render()
{
	if (!isShow_)
	{
		return;
	}
	
	//�U���K�p
	quake_.EnableQuake(QaukeAxis::Y);
	
	//�R���{�r�؂ꎞ�̃t�F�[�h����
	if (isFade_)
	{
		fade_.Update();
		if (fade_.IsEnd())
		{
			fade_.Reset();
			isFade_ = false;
			isShow_ = false;
			return;
		}
	}

	//�����T�C�Y�v�Z
	CRectangle rect;
	const auto str = std::to_string(comboCount_);
	font_->CalculateStringRect(0,0,str.c_str(),rect);

	//�����`��
	auto offset = quake_.GetOffset();
	auto alpha = fade_.GetFadeValue();
	font_->RenderFormatString(position_.x - rect.GetWidth() + offset.x,
		position_.y + offset.y, MOF_ARGB(alpha, 255, 255, 255), str.c_str());
	font_->RenderFormatString(position_.x + offset.x * 0.2f,
		position_.y + offset.y * 0.2f, MOF_ARGB(alpha,255,255, 255), "Combo");

}

void ActionGame::CComboRender::Release()
{
	font_.reset();
}

void ActionGame::CComboRender::SetComboCount(uint32_t count) noexcept
{
	prevComboCount_ = comboCount_;
	
	if (count > 0)
	{
		comboCount_ = count;
		//�U���J�n
		quake_.StartQuake();
		isShow_ = true;

		//�������t�F�[�h��ԂȂ�t�F�[�h���Z�b�g
		if (isFade_)
		{
			fade_.Reset();
			isFade_ = false;
		}
	}
	if (comboCount_ > COMBO_MAX)
	{
		comboCount_ = COMBO_MAX;
	}
}

void ActionGame::CComboRender::SetEndShowTime(float time) noexcept
{
	showEndTime_ = time;
}

void ActionGame::CComboRender::SetCurrentShowTime(float time) noexcept
{
	showTime_ = time;
	if (showTime_ >= showEndTime_)
	{
		isFade_ = true;
		fade_.Start();
	}
}
