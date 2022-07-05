#include "CameraBase.h"

CCameraBase::CCameraBase(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: m_Camera()
	, m_LookPos(0,0,0)
	, m_Position(0,0,0)
	, m_TargetPos(pos)
	, m_TargetLookPos(lookPos)
	, m_OffsetPos(offsetPos)
	, m_OffsetLookPos(offsetLookPos)
	, m_AnimEndFlg(false)
	, m_ResetFlg(false)
	, m_AnimData()
{
	Create();
}

void CCameraBase::Create()
{
	m_Camera.SetViewPort();
	m_Position = m_TargetPos + m_OffsetPos;
	m_LookPos = m_TargetLookPos + m_OffsetLookPos;
	m_Camera.LookAt(m_Position, m_LookPos, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(30), 1920.0f / 1080.0f, 0.01f, 250.0f);
	m_Camera.Update();
}

void CCameraBase::UpdateCamera()
{
	m_Camera.LookAt(m_Position, m_LookPos, Vector3(0, 1, 0));
	m_Camera.Update();
}


void CCameraBase::Render2DDebug()
{
}

void CCameraBase::Enable(const Vector3& pos, const Vector3& lookPos)
{
	m_Position = pos;
	m_LookPos = lookPos;
	UpdateCamera();
}

void CCameraBase::SetAnim(Sample::MyUtilities::ANIMV3_DATA* offsetPos, Sample::MyUtilities::ANIMV3_DATA* offsetLookPos, int size)
{
	m_AnimData.pos = new Sample::MyUtilities::ANIMV3_DATA[size];
	m_AnimData.lookPos = new Sample::MyUtilities::ANIMV3_DATA[size];

	for (int i = 0; i < size; i++)
	{
		m_AnimData.pos[i] = offsetPos[i];
		m_AnimData.lookPos[i] = offsetLookPos[i];
	}
	m_AnimData.flg = true;
	m_AnimData.currentTime = 0.0f;
	m_AnimData.count = size;
}
