#include "CameraController.h"

CCameraController::CCameraController()
{
}

CCameraController::~CCameraController()
{
}

void CCameraController::Initialize()
{
	m_Camera.SetViewPort();
	m_OffsetLookPos = Vector3(1.0f, 2.0f, 0.0f);
	m_OffsetPos = Vector3(1.0f, 4.0f, -15.0f);
	m_Position = m_OffsetPos;
	m_LookPos = m_OffsetLookPos;
	m_Camera.LookAt(m_OffsetPos, m_OffsetLookPos, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(30), 1920.0f / 1080.0f, 0.01f, 150.0f);
	m_Camera.Update();
	CGraphicsUtilities::SetCamera(&m_Camera);
}

void CCameraController::Update(Vector3 pos, Vector3 lookPos)
{
	m_Position = pos + m_OffsetPos;
	m_LookPos = lookPos + m_OffsetLookPos;
	m_Camera.LookAt(pos + m_OffsetPos, lookPos + m_OffsetLookPos, Vector3(0, 1, 0));
	if (g_pInput->IsKeyHold(MOFKEY_1))
	{
		m_OffsetPos.z += 0.05f;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_2))
	{
		m_OffsetPos.z -= 0.05f;
	}
	if (g_pInput->IsKeyHold(MOFKEY_3))
	{
		m_OffsetPos.y += 0.05f;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_4))
	{
		m_OffsetPos.y -= 0.05f;
	}
	m_Camera.Update();
}

void CCameraController::Render2DDebug()
{
	CGraphicsUtilities::RenderString(300, 100, "CameraOff X:%.2f,Y:%.2f,Z:%.2f", m_OffsetPos.x, m_OffsetPos.y, m_OffsetPos.z);
}

