#include "CameraBase.h"


using namespace ActionGame;

CameraBase::CameraBase(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
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

void CameraBase::Create()
{
	m_Camera.SetViewPort();
	m_Position = m_TargetPos + m_OffsetPos;
	m_LookPos = m_TargetLookPos + m_OffsetLookPos;
	m_Camera.LookAt(m_Position, m_LookPos, Vector3(0, 1, 0));
	m_Camera.PerspectiveFov(MOF_ToRadian(30), 1920.0f / 1080.0f, 0.01f, 250.0f);
	m_Camera.Update();
}

void CameraBase::UpdateCamera()
{
	m_Camera.LookAt(m_Position, m_LookPos, Vector3(0, 1, 0));
	m_Camera.Update();
}


void CameraBase::Render2DDebug()
{
}

void CameraBase::Enable(const Vector3& pos, const Vector3& lookPos)
{
	m_Position = pos;
	m_LookPos = lookPos;
	UpdateCamera();
}


void CameraBase::SetAnim(const MyUtilities::ANIM_V3_DATA_ARRAY& offsetPos, const MyUtilities::ANIM_V3_DATA_ARRAY& offsetLookPos)
{
	m_AnimData.Pos = offsetPos;
	m_AnimData.LookPos = offsetLookPos;

	m_AnimData.Flg = true;
	m_AnimData.CurrentTime = 0.0f;
	m_AnimData.Count = offsetPos.size();
}
