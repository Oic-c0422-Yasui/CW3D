#include "CameraBase.h"

CCameraBase::CCameraBase()
	: m_Camera()
	, m_Position(0,0,0)
	, m_LookPos(0,0,0)
	, m_TargetPos(0, 0, 0)
	, m_TargetLookPos(0, 0, 0)
	, m_OffsetPos(0, 0, 0)
	, m_OffsetLookPos(0, 0, 0)
{
}

void CCameraBase::Create()
{
	m_Camera.SetViewPort();
	m_OffsetLookPos = Vector3(0.0f, 2.0f, 0.0f);
	m_OffsetPos = Vector3(0.0f, 4.0f, -15.0f);
	m_Position = m_OffsetPos;
	m_LookPos = m_OffsetLookPos;
	m_Camera.LookAt(m_OffsetPos, m_OffsetLookPos, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(30), 1920.0f / 1080.0f, 0.01f, 150.0f);
	m_Camera.Update();
}

void CCameraBase::UpdateCamera()
{
	m_Camera.LookAt(m_Position, m_LookPos, Vector3(0, 1, 0));
	m_Camera.Update();
}

void CCameraBase::Render2DDebug()
{
}
