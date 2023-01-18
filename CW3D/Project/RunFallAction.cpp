#include "FallAction.h"
#include "RunFallAction.h"


ActionGame::RunFallAction::RunFallAction(Parameter param)
	: Action()
	, m_NowDirection(0)
	, m_Parameter(param)
{
}

void ActionGame::RunFallAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

	auto& vel = Velocity();


	//PLAYER_MAXSPEED
	vel->SetMaxVelocity(m_Parameter.maxVelocty.x, m_Parameter.maxVelocty.z);
	//GRAVITYMAX
	vel->SetMaxGravity(m_Parameter.maxGravity);
	//GRAVITY
	vel->SetGravity(m_Parameter.gravity);

	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
		m_NowDirection = DIRECTION_LEFT;
	}
	else
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
		m_NowDirection = DIRECTION_RIGHT;
	}
}

void ActionGame::RunFallAction::Execution()
{
	auto& vel = Velocity();
	bool isReverse = Transform()->IsReverse();
	float rotateY = Transform()->GetRotateY();

	if (Transform()->IsReverse())
	{
		if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.1f);
			m_NowDirection = DIRECTION_LEFTUP;
		}
		else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.1f);
			m_NowDirection = DIRECTION_LEFTDOWN;
		}
		else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.1f);
			m_NowDirection = DIRECTION_LEFT;
		}
	}
	else
	{
		if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.1f);
			m_NowDirection = DIRECTION_RIGHTUP;
		}
		else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.1f);
			m_NowDirection = DIRECTION_RIGHTDOWN;
		}
		else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.1f);
			m_NowDirection = DIRECTION_RIGHT;
		}
	}
}

void ActionGame::RunFallAction::End()
{
}

void ActionGame::RunFallAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

void ActionGame::RunFallAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::RunFallAction::GetKey() const
{
	return STATE_KEY_RUN_FALL;
}

