#include "NomalCamera.h"

CNomalCamera::CNomalCamera()
	: CCameraBase()
{
}

CNomalCamera::~CNomalCamera()
{
}

void CNomalCamera::Create()
{
	CCameraBase::Create();
}

void CNomalCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos + m_OffsetPos;
	m_Position += (m_TargetPos - m_Position) * 0.05f;
	m_TargetLookPos = lookPos + m_OffsetLookPos;
	m_LookPos += (m_TargetLookPos - m_LookPos) * 0.08f;
	CCameraBase::UpdateCamera();
}
