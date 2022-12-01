#include "InterpolateCamera.h"
#include "TimeScaleController.h"


CInterpolateCamera::CInterpolateCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CCameraBase(pos, lookPos, offsetPos, offsetLookPos)
	, m_NextOffsetLookPos(0, 0, 0)
	, m_NextOffsetPos(0, 0, 0)
	, m_PosAnim()
	, m_LookPosAnim()
{
}

CInterpolateCamera::~CInterpolateCamera()
{
	m_PosAnim.clear();
	m_LookPosAnim.clear();
}

void CInterpolateCamera::Set(float time, MyUtilities::EASING_TYPE ease, const CameraPtr& camera)
{
	m_Time = time;
	Create();
	Vector3 pos(camera->GetPos());
	Vector3 lookPos(camera->GetLookPos());
	m_NextOffsetLookPos = camera->GetOffsetLookPos();
	m_NextOffsetPos = camera->GetOffsetPos();
	m_Ease = ease;
	MyUtilities::ANIM_V3_DATA_ARRAY posAnim(
		{
			{0.0f,m_Position,m_Ease},
			{m_Time,pos,m_Ease},
		}
	);
	MyUtilities::ANIM_V3_DATA_ARRAY lookAnim(
		{
			{0.0f,m_LookPos,m_Ease},
			{m_Time,lookPos,m_Ease},
		}
	);

	m_PosAnim = posAnim;
	m_LookPosAnim = lookAnim;
	
}



void CInterpolateCamera::Create()
{
	m_CurrentTime = 0.0f;
	CCameraBase::Create();
}

void CInterpolateCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	//現在地から目的地までの補間アニメーションを作成
	MyUtilities::ANIM_V3_DATA_ARRAY posAnim(
		{
			{0.0f,m_Position,m_Ease},
			{m_Time,pos + m_NextOffsetPos,m_Ease},
		}
	);
	MyUtilities::ANIM_V3_DATA_ARRAY lookAnim(
		{
			{0.0f,m_LookPos,m_Ease},
			{m_Time,lookPos + m_NextOffsetLookPos,m_Ease},
		}
	);

	//現在地から目的地までの座標で補間アニメーションを行う
	m_Position = MyUtilities::InterpolationAnim(m_CurrentTime, posAnim);
	m_LookPos = MyUtilities::InterpolationAnim(m_CurrentTime, lookAnim);
	if (m_CurrentTime > m_Time)
	{
		m_AnimEndFlg = true;
	}
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	CCameraBase::UpdateCamera();
}

