#include "BossHPRender.h"

ActionGame::BossHPRender::BossHPRender()
	: EnemyHPRender()
	, m_Position(0, 0)
	, m_Offset(0, 0)
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
	m_Offset = Vector2(58, 1);
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
	float parcent = (float)m_HP / (float)m_MaxHP;
	parcent = min(parcent, 1.0f);
	m_CurrentHPPercent = parcent;
	//ŽlŠp‚ÅHPƒQ[ƒW•`‰æ
	m_pFrame->Render(m_Position.x, m_Position.y);

	//•\Ž¦ƒQ[ƒW‚ð™X‚É•Ï‰»‚³‚¹‚é
	if (fabsf(m_CurrentHPGaugePercent - m_CurrentHPPercent) > 0.01f)
	{
		m_CurrentHPGaugePercent += (m_CurrentHPPercent - m_CurrentHPGaugePercent) * 0.02f;
		CRectangle rect(0, 0, m_pDamageBar->GetWidth() * m_CurrentHPGaugePercent, m_pDamageBar->GetHeight());
		m_pDamageBar->Render(m_Position.x + m_Offset.x, m_Position.y + m_Offset.y, rect, MOF_XRGB(218, 93, 98));
	}
	else
	{
		m_CurrentHPGaugePercent = m_CurrentHPPercent;
	}
	CRectangle rect(0, 0, m_pHPBar->GetWidth() * m_CurrentHPPercent, m_pHPBar->GetHeight());

	m_pHPBar->Render(m_Position.x + m_Offset.x, m_Position.y + m_Offset.y, rect);
}

void ActionGame::BossHPRender::Release()
{
	m_pHPBar.reset();
	m_pFrame.reset();
	m_pDamageBar.reset();
}
