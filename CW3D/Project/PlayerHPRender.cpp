#include "PlayerHPRender.h"

ActionGame::CPlayerHPRender::CPlayerHPRender()
	: currentHP_(1.0f)
	, currentGauge_(1.0f)
	, HP_(0)
	, maxHP_(0)
	, position_(0, 0)
	, offset_(0, 0)
{
	position_ = Vector2(763, 1045);
	offset_ = Vector2(58, 1);
}

ActionGame::CPlayerHPRender::~CPlayerHPRender()
{
	Release();
}

bool ActionGame::CPlayerHPRender::Load()

{
	HPBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");
	if (HPBar_ == nullptr)
	{
		return false;
	}

	HPFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPFrame");
	if (HPFrame_ == nullptr)
	{
		return false;
	}

	DamageBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");
	if (DamageBar_ == nullptr)
	{
		return false;
	}

	return true;
}

void ActionGame::CPlayerHPRender::Reset() noexcept
{
	currentHP_ = 1.0f;
	currentGauge_ = 1.0f;
}

void ActionGame::CPlayerHPRender::Render()
{

	float parcent = (float)HP_ / (float)maxHP_;
	parcent = min(parcent, 1.0f);
	currentHP_ = parcent;
	//ŽlŠp‚ÅHPƒQ[ƒW•`‰æ
	HPFrame_->Render(position_.x, position_.y);

	//•\Ž¦ƒQ[ƒW‚ð™X‚É•Ï‰»‚³‚¹‚é
	if (fabsf(currentGauge_ - currentHP_) > 0.01f)
	{
		currentGauge_ += (currentHP_ - currentGauge_) * 0.02f;
		CRectangle rect(0, 0, DamageBar_->GetWidth() * currentGauge_, DamageBar_->GetHeight());
		DamageBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect, MOF_XRGB(218, 93, 98));
	}
	else
	{
		currentGauge_ = currentHP_;
	}
	CRectangle rect(0, 0, HPBar_->GetWidth() * currentHP_, HPBar_->GetHeight());

	HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect);
}

void ActionGame::CPlayerHPRender::Release()
{
	HPBar_.reset();
	HPFrame_.reset();
	DamageBar_.reset();
}
