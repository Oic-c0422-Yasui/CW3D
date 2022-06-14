#include "CameraController.h"

CCameraController::CCameraController()
	: Singleton<CCameraController>()
	
{
}

CCameraController::~CCameraController()
{
}

void CCameraController::Initialize()
{
	for (int i = 0; i < CAMERA_ACTION + 1; i++)
	{
		m_Cameras[i].Camera.SetViewPort();
		m_Cameras[i].OffsetLookPos = Vector3(0.0f, 2.0f, 0.0f);
		m_Cameras[i].OffsetPos = Vector3(0.0f, 4.0f, -15.0f);
		m_Cameras[i].Position = m_Cameras[i].OffsetPos;
		m_Cameras[i].LookPos = m_Cameras[i].OffsetLookPos;
		m_Cameras[i].Camera.LookAt(m_Cameras[i].OffsetPos, m_Cameras[i].OffsetLookPos, Vector3(0, 1, 0));
		m_Cameras[i].Camera.PerspectiveFov(MOF_ToRadian(30), 1920.0f / 1080.0f, 0.01f, 150.0f);
		m_Cameras[i].Camera.Update();
	}

	//m_Camera.SetViewPort();
	//m_OffsetLookPos = Vector3(0.0f, 2.0f, 0.0f);
	//m_OffsetPos = Vector3(0.0f, 4.0f, -15.0f);
	//m_Position = m_OffsetPos;
	//m_LookPos = m_OffsetLookPos;
	//m_Camera.LookAt(m_OffsetPos, m_OffsetLookPos, Vector3(0, 1, 0));
	//m_Camera.PerspectiveFov(MOF_ToRadian(30), 1920.0f / 1080.0f, 0.01f, 150.0f);
	//m_Camera.Update();
	CGraphicsUtilities::SetCamera(&m_Cameras[CAMERA_NOMAL].Camera);
}

void CCameraController::Update(Vector3 pos, Vector3 lookPos)
{
	m_TargetPosition = pos + m_OffsetPos;
	m_Position += (m_TargetPosition - m_Position) * 0.05f;
	m_TargetLookPos = lookPos + m_OffsetLookPos;
	m_LookPos += (m_TargetLookPos - m_LookPos) * 0.07f;
	m_Camera.LookAt(m_Position, m_LookPos, Vector3(0, 1, 0));
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

