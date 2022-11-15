#include "FixedCamera.h"

CFixedCamera::CFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CCameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

CFixedCamera::~CFixedCamera()
{
	m_AnimData.Release();
}

void CFixedCamera::Create()
{
	CCameraBase::Create();
}

void CFixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{

	if (m_AnimData.flg)
	{
		m_OffsetPos = Sample::MyUtilities::InterpolationAnim(m_AnimData.currentTime, m_AnimData.pos, m_AnimData.count);
		m_OffsetLookPos = Sample::MyUtilities::InterpolationAnim(m_AnimData.currentTime, m_AnimData.lookPos, m_AnimData.count);
		m_AnimData.currentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	m_Position	= m_TargetPos + m_OffsetPos;
	m_LookPos	= m_TargetLookPos + m_OffsetLookPos;

	CCameraBase::UpdateCamera();
}
