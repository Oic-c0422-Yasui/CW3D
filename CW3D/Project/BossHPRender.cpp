#include "BossHPRender.h"



ActionGame::BossHPRender::BossHPRender()
	: EnemyHPRender()
	, position_(0, 0)
	, offset_(0, 0)
	, m_HPBar()

{

}

bool ActionGame::BossHPRender::Load()
{
	HPBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");
	HPFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPFrame");
	DamageBar_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");

	return true;
}

void ActionGame::BossHPRender::Initialize()
{
	Load();

	position_ = Vector2(763, 100);
	m_HPBar.CountPos = Vector2(763, 150);
	offset_ = Vector2(58, 1);
	m_HPColors[0] = MOF_XRGB(218, 93, 93);
	m_HPColors[1] = MOF_XRGB(93, 218, 93);
	m_HPColors[2] = MOF_XRGB(93, 93, 218);
	m_HPBar.CurrentColorId = 0;
	m_HPBar.NextColorId = 1;
}

void ActionGame::BossHPRender::Reset() noexcept
{
	currentHPPercent_ = 1.0f;
	currentHPGaugePercent_ = 1.0f;
}

void ActionGame::BossHPRender::Render()
{
	if (!isShow_)
	{
		return;
	}

	//g_pInput->GetMousePos(offset_);
	float parcent = (HP_ % m_HPBar.Limit) / (float)m_HPBar.Limit;
	parcent = min(parcent, 1.0f);
	//HPバーのパーセントが視認不可まで下がればリセット
	if (parcent <= 0.001f && m_HPBar.Count > 0)
	{
		parcent = 1.0f;

	}
	currentHPPercent_ = parcent;

	//現在のHPバーの数
	int currentCount = HP_ / m_HPBar.Limit;
	
	//カウントが減ったら
	if (m_HPBar.Count != currentCount)
	{
		//現在のダメージのパーセントをリセット
		currentHPGaugePercent_ = 1.0f;
		m_HPBar.Count = currentCount;
		SettingNextColor();
	}

	

	//HPフレーム描画
	HPFrame_->Render(position_.x, position_.y);

	if (currentHPPercent_ < 1.0f && m_HPBar.Count > 0)
	{
		CRectangle rect(0, 0, HPBar_->GetWidth(), HPBar_->GetHeight());
		HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect, m_HPColors[m_HPBar.NextColorId]);
	}
	//表示ゲージを徐々に変化させる
	if (fabsf(currentHPGaugePercent_ - currentHPPercent_) > 0.01f)
	{
		currentHPGaugePercent_ += (currentHPPercent_ - currentHPGaugePercent_) * 0.02f;
		CRectangle rect(0, 0, DamageBar_->GetWidth() * currentHPGaugePercent_, DamageBar_->GetHeight());
		DamageBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect);
	}
	else
	{
		currentHPGaugePercent_ = currentHPPercent_;
	}
	CRectangle rect(0, 0, HPBar_->GetWidth() * currentHPPercent_, HPBar_->GetHeight());
	HPBar_->Render(position_.x + offset_.x, position_.y + offset_.y, rect, m_HPColors[m_HPBar.CurrentColorId]);

	CGraphicsUtilities::RenderString(m_HPBar.CountPos.x, m_HPBar.CountPos.y, "×%d", m_HPBar.Count);
}

void ActionGame::BossHPRender::Release()
{
	HPBar_.reset();
	HPFrame_.reset();
	DamageBar_.reset();
}

void ActionGame::BossHPRender::SettingNextColor()
{
	m_HPBar.CurrentColorId = m_HPBar.NextColorId;
	if (m_HPBar.NextColorId + 1 >= _countof(m_HPColors))
	{
		m_HPBar.NextColorId = 0;
	}
	else
	{
		m_HPBar.NextColorId++;
	}
}