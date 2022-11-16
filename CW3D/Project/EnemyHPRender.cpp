#include "EnemyHPRender.h"

Sample::CEnemyHPRender::CEnemyHPRender()
	: m_CurrentHP(1.0f)
	, m_CurrentGauge(1.0f)
	, m_HP(0)
	, m_Position(0, 0, 0)
	, m_ShowFlg(false)
	, m_Offset(0, 0, 0)
	, m_Size(0, 0, 0)
{

}

Sample::CEnemyHPRender::~CEnemyHPRender()
{
	Release();
}

void Sample::CEnemyHPRender::Initialize()
{
	m_pHPBar = Sample::ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "DamageBar");
	m_pFrame = Sample::ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "HPFrame");
	m_pDamageBar = Sample::ResourcePtrManager<CSprite3D>::GetInstance().GetResource("UI", "HPBar");


	m_Offset = Vector3(0, 2, 0);
	m_Size = Vector3(1, 0.85f, 1);
	m_pHPBar->m_Angle.z = MOF_ToRadian(180);
	m_pFrame->m_Angle.z = MOF_ToRadian(180);
	m_pDamageBar->m_Angle.z = MOF_ToRadian(180);
	m_pHPBar->m_Angle.x = MOF_ToRadian(0);
	m_pFrame->m_Angle.x = MOF_ToRadian(0);
	m_pDamageBar->m_Angle.x = MOF_ToRadian(0);
	m_pFrame->m_Scale = m_Size;
	m_pHPBar->m_Scale = m_Size;
	m_pDamageBar->m_Scale = m_Size;
	m_pFrame->m_Color = CVector4(1.0f, 1.0f, 1.0f, 0.75f);

}

void Sample::CEnemyHPRender::Reset() noexcept
{

	m_CurrentHP = 1.0f;
	m_CurrentGauge = 1.0f;

}

void Sample::CEnemyHPRender::Render()
{

	if (!IsShow())
	{
		return;
	}
	m_pFrame->m_Position = m_Position + m_Offset;
	m_pHPBar->m_Position = m_Position + m_Offset;
	m_pDamageBar->m_Position = m_Position + m_Offset;

	float parcent = (float)m_HP / (float)m_MaxHP;
	parcent = min(parcent, 1.0f);
	m_CurrentHP = parcent;
	//ŽlŠp‚ÅHPƒQ[ƒW•`‰æ
	LPCamera cam = CGraphicsUtilities::GetCamera();
	m_pFrame->Update();
	m_pFrame->m_World.Multiply3x3(cam->GetBillBoardMatrix());

	m_pFrame->Render();
	//•\Ž¦ƒQ[ƒW‚ð™X‚É•Ï‰»‚³‚¹‚é
	if (fabsf(m_CurrentGauge - m_CurrentHP) > 0.01f)
	{
		m_CurrentGauge += (m_CurrentHP - m_CurrentGauge) * 0.02f;
		m_pDamageBar->m_Scale.x = m_Size.x * m_CurrentGauge;
		float offset = (m_Size.x - m_pDamageBar->m_Scale.x) * 0.5f;
		m_pDamageBar->m_Position.x = (m_Position.x + m_Offset.x) - offset;
		m_pDamageBar->Update();
		m_pDamageBar->m_World.Multiply3x3(cam->GetBillBoardMatrix());
		m_pDamageBar->Render();
	}
	else
	{
		m_CurrentGauge = m_CurrentHP;
	}
	m_pHPBar->m_Scale.x = m_Size.x * m_CurrentHP;
	float offset = (m_Size.x - m_pHPBar->m_Scale.x) * 0.5f;
	m_pHPBar->m_Position.x = (m_Position.x + m_Offset.x) - offset;
	m_pHPBar->Update();
	m_pHPBar->m_World.Multiply3x3(cam->GetBillBoardMatrix());
	m_pHPBar->Render();

}

void Sample::CEnemyHPRender::Release(void)
{

	m_pHPBar.reset();
	m_pFrame.reset();
	m_pDamageBar.reset();

}
