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
	m_Camera.LookAt(Vector3(0.0f, 3.0f, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(60), 1920.0f / 1080.0f, 0.01f, 100.0f);
	m_Camera.Update();
	CGraphicsUtilities::SetCamera(&m_Camera);
}

void CCameraController::Update(Vector3 pos, Vector3 lookPos)
{
	//m_Camera.LookAt(pos, lookPos, Vector3(0, 1, 0));

	m_Camera.Update();
}
