#include "FollowFixedCamera.h"

using namespace ActionGame;

FollowFixedCamera::FollowFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

FollowFixedCamera::~FollowFixedCamera()
{
	m_AnimData.Release();
}

void FollowFixedCamera::Create()
{
	CameraBase::Create();
}

void FollowFixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos + m_OffsetPos;
	m_TargetLookPos = lookPos + m_OffsetLookPos;
	m_Position = m_TargetPos;
	m_LookPos = m_TargetLookPos;

}
