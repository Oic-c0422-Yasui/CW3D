#include "InterpolateCamera.h"



CInterpolateCamera::CInterpolateCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CCameraBase(pos, lookPos, offsetPos, offsetLookPos)
	, m_NextOffsetLookPos(0,0,0)
	, m_NextOffsetPos(0, 0, 0)
{
}

CInterpolateCamera::~CInterpolateCamera()
{
}

void CInterpolateCamera::Set(float time, Sample::MyUtilities::EASING_TYPE ease, const CameraPtr& camera)
{
	m_Time = time;
	Create();
	Vector3 pos(camera->GetPos());
	Vector3 lookPos(camera->GetLookPos());
	m_NextOffsetLookPos = camera->GetOffsetLookPos();
	m_NextOffsetPos = camera->GetOffsetPos();
	m_Ease = ease;
	Sample::MyUtilities::ANIMV3_DATA posAnim[2] =
	{
		{0.0f,m_Position,m_Ease},
		{m_Time,pos,m_Ease},
	};
	Sample::MyUtilities::ANIMV3_DATA lookAnim[2] =
	{
		{0.0f,m_LookPos,m_Ease},
		{m_Time,lookPos,m_Ease},
	};

	for (int i = 0; i < 2; i++)
	{
		m_PosAnim[i] = posAnim[i];
		m_LookPosAnim[i] = lookAnim[i];
	}
	
}



void CInterpolateCamera::Create()
{
	m_CurrentTime = 0.0f;
	CCameraBase::Create();
}

void CInterpolateCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	Sample::MyUtilities::ANIMV3_DATA posAnim[2] =
	{
		{0.0f,m_Position,m_Ease},
		{m_Time,pos + m_NextOffsetPos,m_Ease},
	};
	Sample::MyUtilities::ANIMV3_DATA lookAnim[2] =
	{
		{0.0f,m_LookPos,m_Ease},
		{m_Time,lookPos + m_NextOffsetLookPos,m_Ease},
	};
	m_Position = Sample::MyUtilities::InterpolationAnim(m_CurrentTime, posAnim, 2);
	m_LookPos = Sample::MyUtilities::InterpolationAnim(m_CurrentTime, lookAnim, 2);
	if (m_CurrentTime > m_Time)
	{
		m_AnimEndFlg = true;
	}
	m_CurrentTime += CUtilities::GetFrameSecond();
	CCameraBase::UpdateCamera();
}

