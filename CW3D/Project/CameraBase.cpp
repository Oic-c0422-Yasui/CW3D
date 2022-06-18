#include "CameraBase.h"

CCameraBase::CCameraBase(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: m_Camera()
	, m_LookPos(0,0,0)
	, m_Position(0,0,0)
	, m_TargetPos(pos)
	, m_TargetLookPos(lookPos)
	, m_OffsetPos(offsetPos)
	, m_OffsetLookPos(offsetLookPos)
	, m_AnimEndFlg(false)
	, m_ResetFlg(false)
{
	Create();
}

void CCameraBase::Create()
{
	m_Camera.SetViewPort();
	m_Position = m_TargetPos + m_OffsetPos;
	m_LookPos = m_TargetLookPos + m_OffsetLookPos;
	m_Camera.LookAt(m_Position, m_LookPos, Vector3(0, 1, 0));
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
