#include "Transform.h"


ActionGame::Transform::Transform()
	: m_Position(0, 0, 0)
	, m_Scale(1, 1, 1)
	, m_Rotate(0, 0, 0)
	, m_World()
	, m_UpdateFlg(false)
	, m_ReverseFlg(false)
	, m_Type()
{
}

void ActionGame::Transform::UpdateMatrix()
{
	CMatrix44 matScale;
	CMatrix44 matRotate;
	matScale.Scaling(m_Scale);
	matRotate.RotationZXY(m_Rotate);
	m_World = matScale * matRotate;

	m_World.SetTranslation(m_Position);

	//m_World *= parent->GetWorld();
}


void ActionGame::Transform::AddPosition(const Vector3& position) noexcept
{
	m_Position += position * TimeScaleControllerInstance.GetTimeScale(m_Type);
	m_World.SetTranslation(m_Position);
}

void ActionGame::Transform::AddPosition(const VelocityPtr& velocity) noexcept
{
	if (velocity->IsGravity())
	{
		m_Position += velocity->GetVelocity() * TimeScaleControllerInstance.GetTimeScale(m_Type);
	}
	else
	{
		m_Position.x += velocity->GetVelocityX() * TimeScaleControllerInstance.GetTimeScale(m_Type);
		m_Position.z += velocity->GetVelocityZ() * TimeScaleControllerInstance.GetTimeScale(m_Type);
	}
	m_World.SetTranslation(m_Position);
}

void ActionGame::Transform::Clip(const Vector3& min, const Vector3& max)
{
	ClipX(min.x, max.x);
	ClipY(min.y, max.y);
	ClipZ(min.z, max.z);
}

void ActionGame::Transform::ClipX(float min, float max)
{
	m_Position.x = ((m_Position.x > max) ?
		max : ((m_Position.x < min) ? min : m_Position.x));
}

void ActionGame::Transform::ClipY(float min, float max)
{
	m_Position.y = ((m_Position.y > max) ?
		max : ((m_Position.y < min) ? min : m_Position.y));
}

void ActionGame::Transform::ClipZ(float min, float max)
{
	m_Position.z = ((m_Position.z > max) ?
		max : ((m_Position.z < min) ? min : m_Position.z));
}

void ActionGame::Transform::SetPosition(const Vector3& position) noexcept
{
	m_Position = position;
	m_World.SetTranslation(m_Position);
}
