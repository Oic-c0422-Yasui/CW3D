#include "FollowFixedCamera.h"

CFollowFixedCamera::CFollowFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CCameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

CFollowFixedCamera::~CFollowFixedCamera()
{
}

void CFollowFixedCamera::Create()
{
	CCameraBase::Create();
}

void CFollowFixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos + m_OffsetPos;
	m_TargetLookPos = lookPos + m_OffsetLookPos;
	m_Position = m_TargetPos;
	m_LookPos = m_TargetLookPos;
	CCameraBase::UpdateCamera();
}
