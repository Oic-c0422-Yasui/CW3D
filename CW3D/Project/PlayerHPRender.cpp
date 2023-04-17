#include "PlayerHPRender.h"
#include "ResourceManager.h"

ActionGame::CPlayerHPRender::CPlayerHPRender()
	: currentGauge_(1.0f)
	, HP_(0)
	, maxHP_(0)
	, position_(0, 0)
	, offset_(0, 0)
{
	position_ = Vector2(630, 1046);
	offset_ = Vector2(46, 3);
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

	damageBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");
	if (damageBar_ == nullptr)
	{
		return false;
	}

	return true;
}

void ActionGame::CPlayerHPRender::Reset() noexcept
{
	currentGauge_ = 1.0f;
}

void ActionGame::CPlayerHPRender::Render()
{

	//ŽlŠp‚ÅHPƒQ[ƒW•`‰æ
	HPFrame_->Render(position_.x, position_.y);

	float parcent = (float)HP_ / (float)maxHP_;
	parcent = min(parcent, 1.0f);
	//•\Ž¦ƒQ[ƒW‚ð™X‚É•Ï‰»‚³‚¹‚é
	if (fabsf(currentGauge_ - parcent) > 0.01f)
	{
		currentGauge_ += (parcent - currentGauge_) * 0.02f;
		CRectangle rect(0, 0, damageBar_->GetWidth() * currentGauge_, damageBar_->GetHeight());
		damageBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect, MOF_XRGB(218, 93, 98));
	}
	else
	{
		currentGauge_ = parcent;
	}
	CRectangle rect(0, 0, HPBar_->GetWidth() * parcent, HPBar_->GetHeight());

	HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect);
}

void ActionGame::CPlayerHPRender::Release()
{
	HPBar_.reset();
	HPFrame_.reset();
	damageBar_.reset();
}
