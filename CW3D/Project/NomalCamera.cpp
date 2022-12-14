#include "NomalCamera.h"

using namespace ActionGame;

NomalCamera::NomalCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos)
	: CameraBase(pos, lookPos, offsetPos, offsetLookPos)
{
}

NomalCamera::~NomalCamera()
{
}

void NomalCamera::Create()
{
	m_OffsetLookPos = Vector3(0.0f, 1.0f, 0.0f);
	m_OffsetPos = Vector3(0.0f, 5.0f, -15.0f);
	CameraBase::Create();
}

void NomalCamera::Update(const Vector3& pos, const Vector3& lookPos)
{
	//íxÇÍÇƒí«è]Ç∑ÇÈèàóù
	m_TargetPos = pos + m_OffsetPos;
	m_Position.x += (m_TargetPos.x - m_Position.x) * 0.08f;
	m_Position.y += (m_TargetPos.y - m_Position.y) * 0.07f;
	m_Position.z += (m_TargetPos.z - m_Position.z) * 0.08f;
	m_TargetLookPos = lookPos + m_OffsetLookPos;
	m_LookPos.x += (m_TargetLookPos.x - m_LookPos.x) * 0.12f;
	m_LookPos.y += (m_TargetLookPos.y - m_LookPos.y) * 0.11f;
	m_LookPos.z += (m_TargetLookPos.z - m_LookPos.z) * 0.12f;

	if (m_ResetFlg)
	{
		m_Position = m_TargetPos;
		m_LookPos = m_TargetLookPos;
		m_ResetFlg = false;
	}
}

void NomalCamera::Enable(const Vector3& pos, const Vector3& lookPos)
{
	m_TargetPos = pos;
	m_LookPos = lookPos;
	m_Position = pos;
	m_LookPos = lookPos;
	CameraBase::UpdateCamera();
}
