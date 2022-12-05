#include "FixedCamera.h"

FixedCamera::FixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CCameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

FixedCamera::~FixedCamera()
{
	m_AnimData.Release();
}

void FixedCamera::Create()
{
	CCameraBase::Create();
}

void FixedCamera::Update(const Vector3& pos, const Vector3& lookPos)
{

	if (m_AnimData.Flg)
	{
		m_OffsetPos = MyUtilities::InterpolationAnim(m_AnimData.CurrentTime, m_AnimData.Pos);
		m_OffsetLookPos = MyUtilities::InterpolationAnim(m_AnimData.CurrentTime, m_AnimData.LookPos);
		m_AnimData.CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	m_Position	= m_TargetPos + m_OffsetPos;
	m_LookPos	= m_TargetLookPos + m_OffsetLookPos;

	CCameraBase::UpdateCamera();
}
