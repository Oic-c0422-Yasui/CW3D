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
	m_OffsetLookPos = Vector3(0.0f, 2.0f, 0.0f);
	m_OffsetPos = Vector3(0.0f, 3.0f, -15.0f);
	m_Camera.LookAt(m_OffsetPos, m_OffsetLookPos, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(30), 1920.0f / 1080.0f, 0.01f, 150.0f);
	m_Camera.Update();
	CGraphicsUtilities::SetCamera(&m_Camera);
}

void CCameraController::Update(Vector3 pos, Vector3 lookPos)
{
	m_Camera.LookAt(pos + m_OffsetPos, lookPos + m_OffsetLookPos, Vector3(0, 1, 0));

	m_Camera.Update();
}
