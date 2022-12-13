#include "MoveAction.h"

ActionGame::MoveAction::MoveAction(Parameter param)
	: Action()
	, m_NowDirection(0)
	, m_Parameter(param)
{
}

void ActionGame::MoveAction::Start()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);

	auto& vel = Velocity();

	vel->SetMaxVelocity(m_Parameter.maxVelocity.x, m_Parameter.maxVelocity.z);

	vel->SetMaxGravity(m_Parameter.maxGravity);

	vel->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

	float rotateY = Transform()->GetRotateY();
	if (Transform()->IsReverse())
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
		m_NowDirection = DIRECTION_RIGHT;
	}
	else
	{
		vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
		m_NowDirection = DIRECTION_LEFT;
	}
}

void ActionGame::MoveAction::Execution()
{

	auto& velocity = Velocity();
	bool isReverse = Transform()->IsReverse();
	float rotateY = Transform()->GetRotateY();

	//左右向き変更
	if (velocity->GetVelocityX() < 0 && !isReverse)
	{
		Transform()->SetReverse(true);


	}
	else if (velocity->GetVelocityX() > 0 && isReverse)
	{
		Transform()->SetReverse(false);

	}

	//進行方向に向きを回転させる
	if (isReverse)
	{
		//左上
		if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.15f);
			m_NowDirection = DIRECTION_LEFTUP;
		}
		//左下
		else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.15f);
			m_NowDirection = DIRECTION_LEFTDOWN;
		}
		//左
		else if (velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
			m_NowDirection = DIRECTION_LEFT;
		}
	}
	else
	{
		//右上
		if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.15f);
			m_NowDirection = DIRECTION_RIGHTUP;
		}
		//右下
		else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.15f);
			m_NowDirection = DIRECTION_RIGHTDOWN;
		}
		//右
		else if (velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
		{
			Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.15f);
			m_NowDirection = DIRECTION_RIGHT;
		}
	}
}

void ActionGame::MoveAction::End()
{
}

void ActionGame::MoveAction::Acceleration(float x, float z)
{

	Velocity()->Acceleration(x * m_Parameter.velocity.x,
		z * m_Parameter.velocity.z);
}

const ActionGame::ActionKeyType ActionGame::MoveAction::GetKey() const
{
	return STATE_KEY_MOVE;
}
