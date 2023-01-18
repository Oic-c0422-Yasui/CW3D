#include "RunJumpAction.h"

ActionGame::RunJumpAction::RunJumpAction(Parameter param)
	: Action()
	, m_Parameter(param)
	, m_NowDirection(0)
{
}

void ActionGame::RunJumpAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
	auto& vel = Velocity();

	//PLAYER_MAXSPEED
	vel->SetMaxVelocity(m_Parameter.maxVelocity.x, m_Parameter.maxVelocity.z);
	//GRAVITYMAX
	vel->SetMaxGravity(m_Parameter.maxGravity);
	//PLAYER_JUMPPOWER
	vel->SetVelocityY(m_Parameter.jumpPower);
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

void ActionGame::RunJumpAction::Execution()
{

	auto& vel = Velocity();
	bool isReverse = Transform()->IsReverse();
	float rotateY = Transform()->GetRotateY();

	if (Transform()->IsReverse())
	{
		if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(135), 0.1f);
			m_NowDirection = DIRECTION_LEFTUP;
		}
		else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(45), 0.1f);
			m_NowDirection = DIRECTION_LEFTDOWN;
		}
		else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.1f);
			m_NowDirection = DIRECTION_LEFT;
		}
	}
	else
	{
		if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(-135), 0.1f);
			m_NowDirection = DIRECTION_RIGHTUP;
		}
		else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(-45), 0.1f);
			m_NowDirection = DIRECTION_RIGHTDOWN;
		}
		else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.1f);
			m_NowDirection = DIRECTION_RIGHT;
		}
	}
}

void ActionGame::RunJumpAction::End()
{
}

void ActionGame::RunJumpAction::Acceleration(float x, float z)
{
	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

void ActionGame::RunJumpAction::Reset()
{
}

const ActionGame::ActionKeyType ActionGame::RunJumpAction::GetKey() const
{
	return STATE_KEY_RUN_JUMP;
}
