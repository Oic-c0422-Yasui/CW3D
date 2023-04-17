#include "MoveAction.h"



ActionGame::CMoveAction::CMoveAction(BaseParameter baseParam, Parameter param)
	: CBaseAction(baseParam)
	, currentDirection_(DIRECTION::RIGHT)
	, parameter_(param)
{
}

void ActionGame::CMoveAction::Start()
{
	CBaseAction::Start();

	auto& vel = Velocity();
	vel->SetMaxVelocity(parameter_.maxVelocity.x, parameter_.maxVelocity.z);
	vel->SetMaxGravity(parameter_.maxGravity);
	vel->SetGravity(parameter_.gravity);
	vel->SetDecelerate(parameter_.decelerate.x, parameter_.decelerate.z);

	//アクターの向きを初期化する
	InitDirection();

	CBaseAction::SetRotation();
}

void ActionGame::CMoveAction::Execution()
{

	auto& vel = Velocity();
	const bool isReverse = Transform()->IsReverse();
	//左右向き変更
	if (vel->GetVelocityX() < 0 && !isReverse)
	{
		Transform()->SetReverse(true);
	}
	else if (vel->GetVelocityX() > 0 && isReverse)
	{
		Transform()->SetReverse(false);
	}

	//アクターの向きを変更する
	ChangeDirection();
	
}

void ActionGame::CMoveAction::End()
{
}

void ActionGame::CMoveAction::Acceleration(float x, float z)
{

	Velocity()->Acceleration(x * parameter_.velocity.x,
		z * parameter_.velocity.z);
}

const ActionGame::ActionKeyType ActionGame::CMoveAction::GetKey() const
{
	return STATE_KEY_MOVE;
}

void ActionGame::CMoveAction::InitDirection()
{
	if (Transform()->IsReverse())
	{
		currentDirection_ = DIRECTION::RIGHT;
	}
	else
	{
		currentDirection_ = DIRECTION::LEFT;
	}
}

void ActionGame::CMoveAction::ChangeDirection()
{
	auto& vel = Velocity();
	const bool isReverse = Transform()->IsReverse();
	const float rotateY = Transform()->GetRotateY();
	
	//進行方向に向きを回転させる
	if (isReverse)
	{
		//左上
		if (vel->GetVelocityZ() > 0 && currentDirection_ != DIRECTION::LEFT_UP)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(135), 0.15f);
			currentDirection_ = DIRECTION::LEFT_UP;
		}
		//左下
		else if (vel->GetVelocityZ() < 0 && currentDirection_ != DIRECTION::LEFT_DOWN)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(45), 0.15f);
			currentDirection_ = DIRECTION::LEFT_DOWN;
		}
		//左
		else if (vel->GetVelocityZ() == 0 && currentDirection_ != DIRECTION::LEFT)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
			currentDirection_ = DIRECTION::LEFT;
		}
	}
	else
	{
		//右上
		if (vel->GetVelocityZ() > 0 && currentDirection_ != DIRECTION::RIGHT_UP)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(-135), 0.15f);
			currentDirection_ = DIRECTION::RIGHT_UP;
		}
		//右下
		else if (vel->GetVelocityZ() < 0 && currentDirection_ != DIRECTION::RIGHT_DOWN)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(-45), 0.15f);
			currentDirection_ = DIRECTION::RIGHT_DOWN;
		}
		//右
		else if (vel->GetVelocityZ() == 0 && currentDirection_ != DIRECTION::RIGHT)
		{
			vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.15f);
			currentDirection_ = DIRECTION::RIGHT;
		}
	}
}