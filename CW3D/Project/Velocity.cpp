#include "Velocity.h"

ActionGame::Velocity::Velocity()
	: m_Velocity(0.0f, 0.0f, 0.0f)
	, m_MaxVelocity(0.0f, 0.0f, 0.0f)
	, m_UpdateVelocity(0.0f, 0.0f, 0.0f)
	, m_Decelerate(0.0f, 0.0f, 0.0f)
	, m_IsGravity(true)
	, m_Gravity(0.0f)
	, m_SetRotateFlg(false)
	, m_CurrentTime(0.0f)
	, m_MoveTime(0.0f)
	, m_TargetY(0.0f)
	, m_StartY(0.0f)
	, m_CurrentY(0.0f)
	, m_Type()
{
}

void ActionGame::Velocity::Update()
{
	//重力の適用
	if (m_IsGravity)
	{
		m_Velocity.y -= m_Gravity * TimeScaleControllerInstance.GetTimeScale(m_Type);
		m_Velocity.y = ((m_Velocity.y < -m_MaxVelocity.y) ?
			-m_MaxVelocity.y : m_Velocity.y);
	}

	//回転の更新
	if (m_SetRotateFlg)
	{
		if (m_CurrentTime <= m_MoveTime)
		{
			m_CurrentY = MyUtilities::RotateTimer(m_StartY, m_CurrentTime, m_TargetY, m_MoveTime);

			m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(m_Type);
		}
		else
		{
			m_CurrentY = m_TargetY;
			m_SetRotateFlg = false;
		}
	}
	//速度の更新を実施
	if (fabsf(m_UpdateVelocity.x) > 0)
	{
		//最大速度を超えるようなら倍速で減速
		if (m_Velocity.x > m_MaxVelocity.x + m_Decelerate.x * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type))
		{
			m_Velocity.x -= m_Decelerate.x * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type);
			if (m_UpdateVelocity.x < 0)
			{
				m_Velocity.x += m_UpdateVelocity.x * TimeScaleControllerInstance.GetTimeScale(m_Type);
			}
		}
		else if (m_Velocity.x < -m_MaxVelocity.x - m_Decelerate.x * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type))
		{
			m_Velocity.x += m_Decelerate.x * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type);
			if (m_UpdateVelocity.x > 0)
			{
				m_Velocity.x += m_UpdateVelocity.x * TimeScaleControllerInstance.GetTimeScale(m_Type);
			}
		}
		else
		{
			m_Velocity.x += m_UpdateVelocity.x * TimeScaleControllerInstance.GetTimeScale(m_Type);
			m_Velocity.x = ((m_Velocity.x > m_MaxVelocity.x) ?
				m_MaxVelocity.x : ((m_Velocity.x < -m_MaxVelocity.x) ?
					-m_MaxVelocity.x : m_Velocity.x));
		}
		m_UpdateVelocity.x = 0;
	}
	else
	{
		m_Velocity.x = ((fabsf(m_Velocity.x) < fabsf(m_Decelerate.x)) ?
			0 : m_Velocity.x - copysignf(m_Decelerate.x, m_Velocity.x));
	}
	if (fabsf(m_UpdateVelocity.z) > 0)
	{
		//最大速度を超えるようなら倍速で減速
		if (m_Velocity.z > m_MaxVelocity.z + m_Decelerate.z * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type))
		{
			m_Velocity.z -= m_Decelerate.z * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type);
			if (m_UpdateVelocity.z < 0)
			{
				m_Velocity.z += m_UpdateVelocity.z * TimeScaleControllerInstance.GetTimeScale(m_Type);
			}
		}
		else if (m_Velocity.z < -m_MaxVelocity.z - m_Decelerate.z * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type))
		{
			m_Velocity.z += m_Decelerate.z * 2 * TimeScaleControllerInstance.GetTimeScale(m_Type);
			if (m_UpdateVelocity.z > 0)
			{
				m_Velocity.z += m_UpdateVelocity.z * TimeScaleControllerInstance.GetTimeScale(m_Type);
			}
		}
		else
		{
			m_Velocity.z += m_UpdateVelocity.z * TimeScaleControllerInstance.GetTimeScale(m_Type);
			m_Velocity.z = ((m_Velocity.z > m_MaxVelocity.z) ?
				m_MaxVelocity.z : ((m_Velocity.z < -m_MaxVelocity.z) ?
					-m_MaxVelocity.z : m_Velocity.z));
		}
		m_UpdateVelocity.z = 0;
	}
	else
	{
		m_Velocity.z = ((fabsf(m_Velocity.z) < fabsf(m_Decelerate.z)) ?
			0 : m_Velocity.z - copysignf(m_Decelerate.z, m_Velocity.z));
	}
}
