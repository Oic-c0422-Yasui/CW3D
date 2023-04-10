#include "BossHPRender.h"



ActionGame::CBossHPRender::CBossHPRender()
	: CEnemyHPRender()
	, position_(0, 0)
	, offset_(0, 0)
	, HPBarParam_()

{

}

bool ActionGame::CBossHPRender::Load()
{
	HPBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");
	HPFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPFrame");
	damageBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");

	return true;
}

void ActionGame::CBossHPRender::Initialize()
{
	Load();

	position_ = Vector2(763, 100);
	HPBarParam_.CountPos = Vector2(763, 150);
	offset_ = Vector2(58, 1);
	HPColors_[0] = MOF_XRGB(218, 93, 93);
	HPColors_[1] = MOF_XRGB(93, 218, 93);
	HPColors_[2] = MOF_XRGB(93, 93, 218);
	HPBarParam_.CurrentColorId = 0;
	HPBarParam_.NextColorId = 1;
}

void ActionGame::CBossHPRender::Reset() noexcept
{
	currentHPPercent_ = 1.0f;
	currentHPGaugePercent_ = 1.0f;
}

void ActionGame::CBossHPRender::Render()
{
	if (!isShow_)
	{
		return;
	}

	float parcent = (HP_ % HPBarParam_.Limit) / (float)HPBarParam_.Limit;
	parcent = min(parcent, 1.0f);
	//HPバーのパーセントが視認不可まで下がればリセット
	if (parcent <= 0.001f && HPBarParam_.Count > 0)
	{
		parcent = 1.0f;
	}
	currentHPPercent_ = parcent;

	//現在のHPバーの数
	int currentCount = HP_ / HPBarParam_.Limit;
	
	//カウントが減ったら
	if (HPBarParam_.Count != currentCount)
	{
		//現在のダメージのパーセントをリセット
		currentHPGaugePercent_ = 1.0f;
		HPBarParam_.Count = currentCount;
		SettingNextColor();
	}

	

	//HPフレーム描画
	HPFrame_->Render(position_.x, position_.y);

	if (currentHPPercent_ < 1.0f && HPBarParam_.Count > 0)
	{
		CRectangle rect(0, 0, HPBar_->GetWidth(), HPBar_->GetHeight());
		HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect, HPColors_[HPBarParam_.NextColorId]);
	}
	//表示ゲージを徐々に変化させる
	if (fabsf(currentHPGaugePercent_ - currentHPPercent_) > 0.01f)
	{
		currentHPGaugePercent_ += (currentHPPercent_ - currentHPGaugePercent_) * 0.02f;
		CRectangle rect(0, 0, damageBar_->GetWidth() * currentHPGaugePercent_, damageBar_->GetHeight());
		damageBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect);
	}
	else
	{
		currentHPGaugePercent_ = currentHPPercent_;
	}
	CRectangle rect(0, 0, HPBar_->GetWidth() * currentHPPercent_, HPBar_->GetHeight());
	HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect, HPColors_[HPBarParam_.CurrentColorId]);

	//HPバーの数
	CGraphicsUtilities::RenderString(HPBarParam_.CountPos.x, HPBarParam_.CountPos.y, "×%d", HPBarParam_.Count);
}

void ActionGame::CBossHPRender::Release()
{
	HPBar_.reset();
	HPFrame_.reset();
	damageBar_.reset();
}

void ActionGame::CBossHPRender::SettingNextColor()
{
	HPBarParam_.CurrentColorId = HPBarParam_.NextColorId;
	if (HPBarParam_.NextColorId + 1 >= _countof(HPColors_))
	{
		HPBarParam_.NextColorId = 0;
	}
	else
	{
		HPBarParam_.NextColorId++;
	}
}