#include "Player.h"



CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load(CMeshContainer* pMesh)
{
	m_pMesh = pMesh;
	if (m_pMesh != nullptr)
	{
		return false;
	}

	return true;
}

void CPlayer::Initialize()
{
	m_Speed = TEMP_SPEED;
	m_Position = Vector3(0, 0, 0);
	m_Velocity = Vector3(0, 0, 0);
	m_Rotation = Vector3(0, 0, 0);
	m_Scale = Vector3(1, 1, 1);
	CMatrix44 matRotate;
	matRotate.RotationY(MOF_ToRadian(-60));
	matWorld *= matRotate;
}

void CPlayer::Update()
{
	UpdateKey();
	UpdateMove();
	SetReverse();

	m_Position += m_Velocity;
}

void CPlayer::Render()
{

	
	matWorld.SetTranslation(m_Position);
	m_pMesh->Render(matWorld);
}

void CPlayer::Release()
{
}

void CPlayer::UpdateKey()
{
	m_HorizontalMoveFlg = false;
	m_VerticalMoveFlg = false;
	if (m_pInput->IsNegativePress(KEY_HORIZONTAL))
	{
		m_HorizontalMoveFlg = true;
		m_ReverseFlg = true;
		m_Velocity.x -= m_Speed * (CUtilities::GetFrameSecond() * 10);
		if (m_Velocity.x < -m_Speed)
		{
			m_Velocity.x = -m_Speed;
		}
	}
	else if (m_pInput->IsPress(KEY_HORIZONTAL))
	{
		m_HorizontalMoveFlg = true;
		m_ReverseFlg = false;
		m_Velocity.x += m_Speed * (CUtilities::GetFrameSecond() * 10);
		if (m_Velocity.x > m_Speed)
		{
			m_Velocity.x = m_Speed;
		}
	}
	if (m_pInput->IsNegativePress(KEY_VERTICAL))
	{
		m_VerticalMoveFlg = true;
		m_Velocity.z += m_Speed * (CUtilities::GetFrameSecond() * 10);
		if (m_Velocity.z > m_Speed)
		{
			m_Velocity.z = m_Speed;
		}
	}
	else if (m_pInput->IsPress(KEY_VERTICAL))
	{
		m_VerticalMoveFlg = true;
		m_Velocity.z -= m_Speed * (CUtilities::GetFrameSecond() * 10);
		if (m_Velocity.z < -m_Speed)
		{
			m_Velocity.z = -m_Speed;
		}
	}
}

void CPlayer::UpdateMove()
{
	if (!m_HorizontalMoveFlg)
	{
		if (m_Velocity.x > 0)
		{
			m_Velocity.x -= m_Speed * (CUtilities::GetFrameSecond() * 10);
			if (m_Velocity.x <= 0)
			{
				m_Velocity.x = 0;
			}
		}
		else if (m_Velocity.x < 0)
		{
			m_Velocity.x += m_Speed * (CUtilities::GetFrameSecond() * 10);
			if (m_Velocity.x >= 0)
			{
				m_Velocity.x = 0;
			}
		}
	}
	if (!m_VerticalMoveFlg)
	{
		if (m_Velocity.z > 0)
		{
			m_Velocity.z -= m_Speed * (CUtilities::GetFrameSecond() * 10);
			if (m_Velocity.z <= 0)
			{
				m_Velocity.z = 0;
			}
		}
		else if (m_Velocity.z < 0)
		{
			m_Velocity.z += m_Speed * (CUtilities::GetFrameSecond() * 10);
			if (m_Velocity.z >= 0)
			{
				m_Velocity.z = 0;
			}
		}
	}
		
	
	
}

void CPlayer::SetReverse()
{
	if (m_ReverseFlg)
	{
		CMatrix44 matRotate;
		matRotate.RotationY(MOF_ToRadian(60));
		matWorld = matRotate;
	}
	else
	{
		CMatrix44 matRotate;
		matRotate.RotationY(MOF_ToRadian(-60));
		matWorld = matRotate;
	}
	
}
