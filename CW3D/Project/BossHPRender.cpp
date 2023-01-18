#include "BossHPRender.h"



ActionGame::BossHPRender::BossHPRender()
	: EnemyHPRender()
	, m_Position(0, 0)
	, m_Offset(0, 0)
	, m_HPBar()

{

}

bool ActionGame::BossHPRender::Load()
{
	m_pHPBar = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");
	m_pFrame = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPFrame");
	m_pDamageBar = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");

	return true;
}

void ActionGame::BossHPRender::Initialize()
{
	Load();

	m_Position = Vector2(763, 100);
	m_HPBar.CountPos = Vector2(763, 150);
	m_Offset = Vector2(58, 1);
	m_HPColors[0] = MOF_XRGB(218, 93, 93);
	m_HPColors[1] = MOF_XRGB(93, 218, 93);
	m_HPColors[2] = MOF_XRGB(93, 93, 218);
	m_HPBar.CurrentColorId = 0;
	m_HPBar.NextColorId = 1;
}

void ActionGame::BossHPRender::Reset() noexcept
{
	m_CurrentHPPercent = 1.0f;
	m_CurrentHPGaugePercent = 1.0f;
}

void ActionGame::BossHPRender::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}

	//g_pInput->GetMousePos(m_Offset);
	float parcent = (m_HP % m_HPBar.Limit) / (float)m_HPBar.Limit;
	parcent = min(parcent, 1.0f);
	//HPバーのパーセントが視認不可まで下がればリセット
	if (parcent <= 0.001f && m_HPBar.Count > 0)
	{
		parcent = 1.0f;

	}
	m_CurrentHPPercent = parcent;

	//現在のHPバーの数
	int currentCount = m_HP / m_HPBar.Limit;
	
	//カウントが減ったら
	if (m_HPBar.Count != currentCount)
	{
		//現在のダメージのパーセントをリセット
		m_CurrentHPGaugePercent = 1.0f;
		m_HPBar.Count = currentCount;
		SettingNextColor();
	}

	

	//HPフレーム描画
	m_pFrame->Render(m_Position.x, m_Position.y);

	if (m_CurrentHPPercent < 1.0f && m_HPBar.Count > 0)
	{
		CRectangle rect(0, 0, m_pHPBar->GetWidth(), m_pHPBar->GetHeight());
		m_pHPBar->Render(m_Position.x + m_Offset.x, m_Position.y + m_Offset.y, rect, m_HPColors[m_HPBar.NextColorId]);
	}
	//表示ゲージを徐々に変化させる
	if (fabsf(m_CurrentHPGaugePercent - m_CurrentHPPercent) > 0.01f)
	{
		m_CurrentHPGaugePercent += (m_CurrentHPPercent - m_CurrentHPGaugePercent) * 0.02f;
		CRectangle rect(0, 0, m_pDamageBar->GetWidth() * m_CurrentHPGaugePercent, m_pDamageBar->GetHeight());
		m_pDamageBar->Render(m_Position.x + m_Offset.x, m_Position.y + m_Offset.y, rect);
	}
	else
	{
		m_CurrentHPGaugePercent = m_CurrentHPPercent;
	}
	CRectangle rect(0, 0, m_pHPBar->GetWidth() * m_CurrentHPPercent, m_pHPBar->GetHeight());
	m_pHPBar->Render(m_Position.x + m_Offset.x, m_Position.y + m_Offset.y, rect, m_HPColors[m_HPBar.CurrentColorId]);

	CGraphicsUtilities::RenderString(m_HPBar.CountPos.x, m_HPBar.CountPos.y, "×%d", m_HPBar.Count);
}

void ActionGame::BossHPRender::Release()
{
	m_pHPBar.reset();
	m_pFrame.reset();
	m_pDamageBar.reset();
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