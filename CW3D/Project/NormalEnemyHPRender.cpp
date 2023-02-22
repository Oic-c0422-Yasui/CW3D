#include "NormalEnemyHPRender.h"


ActionGame::NormalEnemyHPRender::NormalEnemyHPRender()
	: ActionGame::EnemyHPRender()
	, position_(0, 0, 0)
	, offset_(0, 0, 0)
	, m_Size(0, 0, 0)
{

}

ActionGame::NormalEnemyHPRender::~NormalEnemyHPRender()
{
	Release();
}

bool ActionGame::NormalEnemyHPRender::Load()
{
	m_pHPBar = ActionGame::ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "DamageBar");
	m_pFrame = ActionGame::ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "HPFrame");
	m_pDamageBar = ActionGame::ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "HPBar");
	return true;
}

void ActionGame::NormalEnemyHPRender::Initialize()
{
	Load();


	offset_ = Vector3(0, 2, 0);
	m_Size = Vector3(1, 0.85f, 1);
	m_pHPBar->m_Angle.z = MOF_ToRadian(180);
	m_pFrame->m_Angle.z = MOF_ToRadian(180);
	m_pDamageBar->m_Angle.z = MOF_ToRadian(180);
	m_pHPBar->m_Angle.x = MOF_ToRadian(0);
	m_pFrame->m_Angle.x = MOF_ToRadian(0);
	m_pDamageBar->m_Angle.x = MOF_ToRadian(0);
	m_pFrame->scale_ = m_Size;
	m_pHPBar->scale_ = m_Size;
	m_pDamageBar->scale_ = m_Size;
	m_pFrame->m_Color = CVector4(1.0f, 1.0f, 1.0f, 0.75f);

}

void ActionGame::NormalEnemyHPRender::Reset() noexcept
{
	m_CurrentHPPercent = 1.0f;
	m_CurrentHPGaugePercent = 1.0f;
}

void ActionGame::NormalEnemyHPRender::Render()
{

	if (!m_ShowFlg)
	{
		return;
	}

	m_pFrame->position_ = position_ + offset_;
	m_pHPBar->position_ = position_ + offset_;
	m_pDamageBar->position_ = position_ + offset_;

	float parcent = (float)m_HP / (float)m_MaxHP;
	parcent = min(parcent, 1.0f);
	m_CurrentHPPercent = parcent;
	//ŽlŠp‚ÅHPƒQ[ƒW•`‰æ
	LPCamera cam = CGraphicsUtilities::GetCamera();
	m_pFrame->Update();
	m_pFrame->world_.Multiply3x3(cam->GetBillBoardMatrix());

	m_pFrame->Render();
	//•\Ž¦ƒQ[ƒW‚ð™X‚É•Ï‰»‚³‚¹‚é
	if (fabsf(m_CurrentHPGaugePercent - m_CurrentHPPercent) > 0.01f)
	{
		m_CurrentHPGaugePercent += (m_CurrentHPPercent - m_CurrentHPGaugePercent) * 0.02f;
		m_pDamageBar->scale_.x = m_Size.x * m_CurrentHPGaugePercent;
		float offset = (m_Size.x - m_pDamageBar->scale_.x) * 0.5f;
		m_pDamageBar->position_.x = (position_.x + offset_.x) - offset;
		m_pDamageBar->Update();
		m_pDamageBar->world_.Multiply3x3(cam->GetBillBoardMatrix());
		m_pDamageBar->Render();
	}
	else
	{
		m_CurrentHPGaugePercent = m_CurrentHPPercent;
	}

	m_pHPBar->scale_.x = m_Size.x * m_CurrentHPPercent;
	float offset = (m_Size.x - m_pHPBar->scale_.x) * 0.5f;
	m_pHPBar->position_.x = (position_.x + offset_.x) - offset;
	m_pHPBar->Update();
	m_pHPBar->world_.Multiply3x3(cam->GetBillBoardMatrix());
	m_pHPBar->Render();

}

void ActionGame::NormalEnemyHPRender::Release(void)
{

	m_pHPBar.reset();
	m_pFrame.reset();
	m_pDamageBar.reset();

}
