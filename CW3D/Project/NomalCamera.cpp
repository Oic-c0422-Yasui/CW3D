#include "NomalCamera.h"

CNomalCamera::CNomalCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CCameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

CNomalCamera::~CNomalCamera()
{
}

void CNomalCamera::Create()
{
	m_OffsetLookPos = Vector3(0.0f, 1.5f, 0.0f);
	m_OffsetPos = Vector3(0.0f, 4.0f, -15.0f);
	CCameraBase::Create();
}

void CNomalCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos + m_OffsetPos;
	m_Position += (m_TargetPos - m_Position) * 0.05f;
	m_TargetLookPos = lookPos + m_OffsetLookPos;
	m_LookPos += (m_TargetLookPos - m_LookPos) * 0.08f;
	if (m_ResetFlg)
	{
		m_Position = m_TargetPos;
		m_LookPos = m_TargetLookPos;
		m_ResetFlg = false;
	}
	//CCameraBase::UpdateCamera();
}

void CNomalCamera::Enable(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos;
	m_LookPos = lookPos;
	m_Position = pos;
	m_LookPos = lookPos;
	CCameraBase::UpdateCamera();
}
