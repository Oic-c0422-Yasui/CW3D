#include "BossHPRender.h"
#include "AnimationUtilities.h"


ActionGame::CBossHPRender::CBossHPRender()
	: CEnemyHPRender()
	, position_(0, 0)
	, offset_(0, 0)
	, HPBarParam_()

{

}

bool ActionGame::CBossHPRender::Load()
{
	HPBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "BossHPBar");
	HPFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "BossHPFrame");
	damageBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "BossHPBar");

	return true;
}

void ActionGame::CBossHPRender::Initialize()
{
	Load();

	position_ = Vector2(763, 100);
	HPBarParam_.CountPos = Vector2(763, 150);
	offset_ = Vector2(58, 1);
	HPColor_ = HPBarParam_.StartColor;
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
		if (HPBarParam_.Count > HPBarParam_.MaxCount)
		{
			HPBarParam_.MaxCount = HPBarParam_.Count;
		}
		SettingNextColor();
	}

	

	//HPフレーム描画
	HPFrame_->Render(position_.x, position_.y);

	if (currentHPPercent_ < 1.0f && HPBarParam_.Count > 0)
	{
		CRectangle rect(0, 0, HPBar_->GetWidth(), HPBar_->GetHeight());
		HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect, MOF_XRGB(HPColor_, HPColor_, HPColor_));
	}
	//表示ゲージを徐々に変化させる
	if (fabsf(currentHPGaugePercent_ - currentHPPercent_) > 0.01f)
	{
		currentHPGaugePercent_ += (currentHPPercent_ - currentHPGaugePercent_) * 0.02f;
		CRectangle rect(0, 0, damageBar_->GetWidth() * currentHPGaugePercent_, damageBar_->GetHeight());
		damageBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect,MOF_XRGB(218, 93, 93));
	}
	else
	{
		currentHPGaugePercent_ = currentHPPercent_;
	}
	CRectangle rect(0, 0, HPBar_->GetWidth() * currentHPPercent_, HPBar_->GetHeight());
	HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect);

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
	float gauge = (float)(HPBarParam_.MaxCount - HPBarParam_.Count);
	float endColor = HPBarParam_.EndColor;
	HPColor_ = MyUtil::Timer(HPColor_, gauge, endColor, HPBarParam_.MaxCount);
}