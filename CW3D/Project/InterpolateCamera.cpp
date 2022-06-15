#include "InterpolateCamera.h"



CInterpolateCamera::CInterpolateCamera()
	: CCameraBase()
{
}

CInterpolateCamera::~CInterpolateCamera()
{
}

void CInterpolateCamera::Set(float time, Sample::MyUtilities::EASING_TYPE ease, const CameraPtr& camera)
{
	m_Time = time;

	Vector3 pos(camera->GetPos());
	Vector3 lookPos(camera->GetLookPos());

	Sample::MyUtilities::ANIMV3_DATA posAnim[2] =
	{
		{0.0f,m_Position,ease},
		{time,pos,ease},
	};
	Sample::MyUtilities::ANIMV3_DATA lookAnim[2] =
	{
		{0.0f,m_LookPos,ease},
		{time,lookPos,ease},
	};

	for (int i = 0; i < 2; i++)
	{
		m_PosAnim[i] = posAnim[i];
		m_LookPosAnim[i] = lookAnim[i];
	}


}



void CInterpolateCamera::Create()
{
	CCameraBase::Create();
}

void CInterpolateCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos + m_OffsetPos;

	m_Position = Sample::MyUtilities::InterpolationAnim(m_CurrentTime, m_PosAnim, 2);
	m_LookPos = Sample::MyUtilities::InterpolationAnim(m_CurrentTime, m_LookPosAnim, 2);
	
	CCameraBase::UpdateCamera();
}

