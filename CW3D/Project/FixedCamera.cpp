#include "FixedCamera.h"

CFixedCamera::CFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CCameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

CFixedCamera::~CFixedCamera()
{
}

void CFixedCamera::Create()
{
	CCameraBase::Create();
}

void CFixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos + m_OffsetPos;
	m_TargetLookPos = lookPos + m_OffsetLookPos;
	CCameraBase::UpdateCamera();
}
